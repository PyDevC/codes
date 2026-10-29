import triton
import functools
import operator

DEVICE = triton.runtime.driver.active.get_active_torch_device()

@triton.testing.perf_report(
    triton.testing.Benchmark(
        x_names=['M', 'N', 'K'],
        x_vals=[],
        line_arg='provider',
        line_vals=['triton', 'torch'],
        line_names=['Triton', 'Torch'],
        styles=[('blue', '-'), ('green', '-')],
        ylabel='GB/s',
        plot_name='',
        args={},
    ))
def benchmark(fn_triton, fn_torch, create_tensor_fn, M, N, K, provider, dtype):
    size = [M, N, K]
    input_tensors = create_tensor_fn(size, DEVICE, dtype)
    quantiles = [0.5, 0.2, 0.8]
    if provider == "triton":
        ms, min_ms, max_ms = triton.testing.do_bench(lambda: fn_triton(input_tensors), warmup=5, rep=10, quantiles=quantiles)
    elif provider == "torch":
        ms, min_ms, max_ms = triton.testing.do_bench(lambda: fn_torch(input_tensors), warmup=5, rep=10, quantiles=quantiles)
    else:
        raise ValueError(f"No providers as {provider}.")

    numel = input_tensors[0].numel()
    element_size = dtype.itemsize
    gbps = lambda ms: 3 * numel * element_size * 1e-9 / (ms * 1e-3)
    return gbps(ms), gbps(max_ms), gbps(min_ms)

def run_bench(fn_triton, fn_torch, create_tensor_fn, dtype, plot_name):
    benchmark.benchmarks.args = {
        'fn_triton': fn_triton,
        'fn_torch': fn_torch,
        'dtype': dtype,
        'create_tensor_fn': create_tensor_fn
    }

    benchmark.benchmarks.plot_name = plot_name
    benchmark.benchmarks.x_vals = [
        [10, 10, 10],
        [10, 8, 10],
        [1000, 8, 10],
        [128, 32, 256],
        [1000, 8, 10000],
        [1000, 8000, 1000],
        [512, 512, 512],
        [1024, 1024, 1024],
    ]

    benchmark.run(print_data=True)
