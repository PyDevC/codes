from typing import List

import torch
import torch.nn.functional as F
import triton
import triton.language as tl

from benchmark.benchmark import run_bench

DEVICE = triton.runtime.driver.active.get_active_torch_device()

@triton.jit
def softmax_kernel(x_ptr, o_ptr, size, BLOCK_SIZE:tl.constexpr):
    pid = tl.program_id(0)
    block_start = pid * BLOCK_SIZE

    offset = block_start + tl.arange(0, BLOCK_SIZE)
    mask = offset < size
    
    x = tl.load(x_ptr + offset, mask=mask, other=-float('inf'))
    x_max = tl.max(x, axis=0)
    out = tl.exp(x - x_max) / tl.sum(tl.exp(x - x_max), axis=0)
    tl.store(o_ptr + offset, out, mask=mask)

def softmax(x: torch.Tensor):
    output = torch.empty_like(x)
    n_size = output.numel()

    grid = lambda meta: (triton.cdiv(n_size, meta['BLOCK_SIZE']),)
    softmax_kernel[grid](x, output, n_size, BLOCK_SIZE=1024)

    return output

@triton.autotune(
    configs=[
        triton.Config({'BLOCK_SIZE': 128}, num_warps=4),
        triton.Config({'BLOCK_SIZE': 256}, num_warps=4),
        triton.Config({'BLOCK_SIZE': 512}, num_warps=8),
        triton.Config({'BLOCK_SIZE': 1024}, num_warps=8),
    ],
    key=['size'],
)
@triton.jit
def builtin_softmax_kernel(x_ptr, o_ptr, size, BLOCK_SIZE: tl.constexpr):
    pid = tl.program_id(0)
    block_start = pid * BLOCK_SIZE

    offset = block_start + tl.arange(0, BLOCK_SIZE)
    mask = offset < size
    
    x = tl.load(x_ptr + offset, mask=mask, other=-float('inf'))
    out = tl.softmax(x, dim=0)
    tl.store(o_ptr + offset, out, mask=mask)

def builtin_softmax(x_list: List[torch.Tensor]):
    x = x_list[0]
    output = torch.empty_like(x)
    n_size = output.numel()

    block_size = 1024 
    while block_size > n_size and block_size > 32:
        block_size //= 2

    grid = lambda meta: (triton.cdiv(n_size, meta['BLOCK_SIZE']),)
    builtin_softmax_kernel[grid](x, output, n_size)

    return output

def torch_softmax(x: List[torch.Tensor]):
    return torch.softmax(x[0], dim=0)

def make_tensor(size, device, dtype):
    return [torch.rand(size, device=device, dtype=dtype)]

run_bench(builtin_softmax, torch_softmax, make_tensor, dtype=torch.float32, plot_name='fused_softmax')
