import torch
import triton
import triton.language as tl

DEVICE = triton.runtime.driver.active.get_active_torch_device()

@triton.jit
def _add_constant_kernel(x_ptr, numel, c, BLOCK_SIZE: tl.constexpr):
    pid = tl.program_id(0)
    block_start = pid * BLOCK_SIZE
    offsets = block_start + tl.arange(0, BLOCK_SIZE)
    mask = offsets < numel

    x = tl.load(x_ptr + offsets, mask=mask)
    x = x + c
    tl.store(x_ptr + offsets, x, mask=mask)

def add_constant(x: torch.Tensor):
    numel = x.numel()
    grid = lambda meta: (1, )
    _add_constant_kernel[grid](x, numel, 10, BLOCK_SIZE=numel)
    return x

t = torch.rand(2**16, device=DEVICE)
print(add_constant(t))
