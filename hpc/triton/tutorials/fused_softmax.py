import torch
import torch.nn.functional as F
import triton
import triton.language as tl

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

def builtin_softmax(x: torch.Tensor):
    output = torch.empty_like(x)
    n_size = output.numel()

    block_size = 1024 
    while block_size > n_size and block_size > 32:
        block_size //= 2

    grid = lambda meta: (triton.cdiv(n_size, meta['BLOCK_SIZE']),)
    builtin_softmax_kernel[grid](x, output, n_size)

    return output

def simple_softmax(x: torch.Tensor):
    x_max = x.max()
    soft = torch.exp(x - x_max) / sum([torch.exp(j - x_max) for j in x])
    return soft

model = torch.compile(lambda x: F.softmax(x, dim=0))

def test():
    x = torch.randn(10, device=DEVICE)
    # x = torch.tensor([2000.0, 10000.0, 1000.1], device=DEVICE, dtype=torch.float64)

    print(simple_softmax(x))
    print(F.softmax(x, dim=0))
    print(builtin_softmax(x))
    print(softmax(x))


@triton.testing.perf_report(
    triton.testing.Benchmark(
        x_names=['size'],
        x_vals=[2**i for i in range(25, 27)],
        x_log=True,
        line_arg='provider',
        line_vals=['builtin triton softmax', 'simple softmax', 'torch', 'triton'],
        line_names=['builtin-softmax', 'simple-softmax', 'torch', 'Triton'],
        ylabel="GB/s",
        plot_name='softmax performance',
        args={}
    )
)
def benchmark(size, provider):
    x = torch.randn(size, device=DEVICE, dtype=torch.float32)
    quantiles = [0.5, 0.2, 0.8]

    if provider == "torch":
        ms, min_ms, max_ms = triton.testing.do_bench(lambda: model(x), quantiles=quantiles)
    elif provider == "triton":
        ms, min_ms, max_ms = triton.testing.do_bench(lambda: softmax(x), quantiles=quantiles)
    elif provider == "simple softmax":
        if size > 100000:  
            ms, min_ms, max_ms = 0.0, 0.0, 0.0
        else:
            ms, min_ms, max_ms = triton.testing.do_bench(lambda: simple_softmax(x), quantiles=quantiles)
    elif provider == "builtin triton softmax":
        ms, min_ms, max_ms = triton.testing.do_bench(lambda: builtin_softmax(x), quantiles=quantiles)

    if ms == 0:
        return 0.0, 0.0, 0.0

    gbps = lambda t: (3 * x.numel() * x.element_size() * 1e-9) / (t * 1e-3) if t > 0 else 0.0

    return gbps(ms), gbps(min_ms), gbps(max_ms)

# test()
benchmark.run(print_data=True)
