import triton
import functools
import operator

DEVICE = triton.runtime.driver.active.get_active_torch_device()

@triton.testing.perf_report(
    triton.testing.Benchmark(
        x_names=['size'],
        x_vals=[2**i for i in range(12, 20)],
        line_arg='provider',
        line_vals=['triton', 'torch'],
        line_names=['Triton', 'Torch'],
        styles=[('blue', '-'), ('green', '-')],
        ylabel='TFLOPS',
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

    flops = 2 * (size ** 3)
    tflops = lambda ms: flops * 1e-12 / (ms * 1e-3)
    return tflops(ms), tflops(max_ms), tflops(min_ms)

def get_benchmark_fn():
    return benchmark

def run_bench(fn_triton, fn_torch, create_tensor_fn, dtype, plot_name, benchmark_fn=None):
    if benchmark_fn is None:
        benchmark_fn = get_benchmark_fn()
        benchmark.benchmarks.args = {
            'fn_triton': fn_triton,
            'fn_torch': fn_torch,
            'dtype': dtype,
            'create_tensor_fn': create_tensor_fn
        }

    benchmark_fn.benchmarks.plot_name = plot_name
    benchmark_fn.run(print_data=True)
