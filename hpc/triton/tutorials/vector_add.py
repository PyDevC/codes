from typing import List

import torch
import triton
import triton.language as tl

from benchmark.benchmark import run_bench

@triton.jit
def add_kernel(x_ptr, y_ptr, o_ptr, size, BLOCK_SIZE: tl.constexpr):
    """Add kernel for x, y

    Parameter:
        x_ptr: pointer to the first tensor
        y_ptr: pointer to the second tensor
        o_ptr: pointer to the output tensor
        size: size of tensor, should be same for all three
        BLOCK_SIZE: block size of the computation
    """
    pid = tl.program_id(0)
    block_start = pid * BLOCK_SIZE
    offsets = block_start + tl.arange(0, BLOCK_SIZE)

    # mask is a boolean array of size 1024
    ## Assumption: you need mask for cases where the block size is not div by num elements
    ## Assumption is correct
    mask = offsets < size

    ## Load the tensor elements to from the offset till the mask length
    x = tl.load(x_ptr + offsets, mask=mask)
    y = tl.load(y_ptr + offsets, mask=mask)

    out = x + y

    tl.store(o_ptr + offsets, out, mask=mask)

def add(x: torch.Tensor, y: torch.Tensor, block_size=1024):
    """Add kernel helper function to invoke `add_kernel`"""

    output = torch.empty_like(x)
    n_size = output.numel()

    # computation grid
    grid = lambda meta: (triton.cdiv(n_size, meta['BLOCK_SIZE']), )
    add_kernel[grid](x, y, output, n_size, BLOCK_SIZE=block_size)

    return output

def torch_add(input_tensors: List[torch.Tensor]):
    return torch.add(input_tensors[0], input_tensors[1])

def triton_add(input_tensors: List[torch.Tensor]):
    return add(input_tensors[0], input_tensors[1])

def make_tensor(size, device, dtype):
    x = torch.rand(size, device=device, dtype=dtype)
    y = torch.rand(size, device=device, dtype=dtype)
    return [x, y]

run_bench(triton_add, torch_add, make_tensor, dtype=torch.float32, plot_name='vector-addition')
