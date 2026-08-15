import torch
import triton
import triton.language as tl

DEVICE = triton.runtime.driver.active.get_active_torch_device()

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

def test_run():
    size = 1024
    x = torch.randn(size, device=DEVICE)
    y = torch.randn(size, device=DEVICE)

    print(add(x, y))


@triton.testing.perf_report(
    triton.testing.Benchmark(
        x_names=['size'],
        x_vals=[2**i for i in range(12, 30, 1)],
        x_log=True,
        line_arg='provider',
        line_vals=['torch', 'triton'],
        line_names=['torch', 'Triton'],
        plot_name='vector addition performance',
        args={}
    )
)
def benchmark(size, provider):
    x = torch.randn(size, device=DEVICE)
    y = torch.randn(size, device=DEVICE)
    quantiles = [0.5, 0.2, 0.8] # what are these?
    if provider == "torch":
        ms, min_ms, max_ms = triton.testing.do_bench(lambda: x + y, quantiles=quantiles)
    if provider == "triton":
        ms, min_ms, max_ms = triton.testing.do_bench(lambda: add(x, y), quantiles=quantiles)

    gbps = lambda ms: 3 * x.numel() * x.element_size() * 1e-9 / (ms * 1e-3)

    return gbps(ms), gbps(min_ms), gbps(max_ms)

benchmark.run(print_data=True)
