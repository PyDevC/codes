from typing import Any, List

import torch
import triton
import triton.language as tl

from benchmark.benchmark import run_bench, DEVICE

@triton.jit
def dropout_kernel(x_ptr, m_ptr, o_ptr, numel, P, BLOCK_SIZE: tl.constexpr):
    pid = tl.program_id(0)
    block_start = pid * BLOCK_SIZE
    offsets = block_start + tl.arange(0, BLOCK_SIZE)
    mask = offsets < numel
    x = tl.load(x_ptr + offsets, mask)
    m = tl.load(m_ptr + offsets, mask)
    out = tl.where(m, x / (1 - P), 0.0)
    tl.store(o_ptr + offsets, out, mask)

def naive_dropout(x: torch.Tensor, x_keep: torch.Tensor, p=0.2):
    output = torch.empty_like(x)
    numel = x.numel()
    grid = lambda meta: (triton.cdiv(numel, meta['BLOCK_SIZE']), )
    dropout_kernel[grid](x, x_keep, output, numel, p, BLOCK_SIZE=1024)
    return output

@triton.jit
def seeded_kernel(x_ptr, o_ptr, numel, P, seed, BLOCK_SIZE: tl.constexpr):
    pid = tl.program_id(0)
    block_start = pid * BLOCK_SIZE
    offsets = block_start + tl.arange(0, BLOCK_SIZE)
    mask = offsets < numel
    x = tl.load(x_ptr + offsets, mask)
    random = tl.rand(seed, offsets)
    x_keep = random > P
    out = tl.where(x_keep, x / (1 - P), 0.0)
    tl.store(o_ptr + offsets, out, mask=mask)

def seeded_dropout(x: torch.Tensor, p):
    output = torch.empty_like(x)
    numel = x.numel()
    grid = lambda meta: (triton.cdiv(numel, meta['BLOCK_SIZE']), )
    seeded_kernel[grid](x, output, numel, p, 1212, BLOCK_SIZE=1024)
    return output

def triton_fn(input_tensors: List[Any]):
    x = input_tensors[0]
    x_keep = input_tensors[1]
    p = input_tensors[2]

    return seeded_dropout(x, p)

def torch_fn(input_tensors: List[Any]):
    x = input_tensors[0]
    p = input_tensors[2]

    return torch.dropout(x, p, train=False)

def make_tensor(size, device, dtype):
    x = torch.rand(size=(size,), device=device, dtype=dtype)
    p = 0.2
    x_keep = (torch.rand(size=(size, ), device=device) > p).to(dtype)
    return [x, x_keep, p]

run_bench(triton_fn, torch_fn, make_tensor, dtype=torch.float32, plot_name="dropout")
