import triton
import functools
import operator

DEVICE = triton.runtime.driver.active.get_active_torch_device()

@triton.testing.perf_report(
    triton.testing.Benchmark(
        x_names=['size'],
        x_vals=[2**i for i in range(12, 28, 1)],
        line_arg='provider',
        line_vals=['triton', 'torch'],
        line_names=['Triton', 'Torch'],
        styles=[('blue', '-'), ('green', '-')],
        ylabel='GB/s',
        plot_name='',
        args={},
    ))
def benchmark(fn_triton, fn_torch, create_tensor_fn, size, provider, dtype):
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

    benchmark.run(print_data=True)
