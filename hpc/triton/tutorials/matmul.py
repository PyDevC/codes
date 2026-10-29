from typing import List

import torch
import triton
import triton.language as tl

from benchmark.benchmark import run_bench

@triton.jit
def simple_matmul_kernel(x_ptr, y_ptr, o_ptr, 
                         M, N, K, 
                         stride_xm, stride_xk,
                         stride_yk, stride_yn,
                         stride_om, stride_on,
                         BLOCK_SIZE_M:tl.constexpr, 
                         BLOCK_SIZE_N: tl.constexpr, 
                         BLOCK_SIZE_K: tl.constexpr,
                         GROUP_SIZE_M: tl.constexpr
):
    pid = tl.program_id(axis=0)
    num_pid_m = tl.cdiv(M, BLOCK_SIZE_M)
    num_pid_n = tl.cdiv(N, BLOCK_SIZE_N)
    num_pid_in_group = GROUP_SIZE_M * num_pid_n
    group_id = pid // num_pid_in_group
    first_pid_m = group_id * GROUP_SIZE_M
    group_size_m = min(num_pid_m - first_pid_m, GROUP_SIZE_M)
    pid_m = first_pid_m + ((pid % num_pid_in_group) % group_size_m)
    pid_n = (pid % num_pid_in_group) // group_size_m
    offset_X_m = (pid_m * BLOCK_SIZE_M + tl.arange(0, BLOCK_SIZE_M)) % M
    offset_Y_n = (pid_n * BLOCK_SIZE_N + tl.arange(0, BLOCK_SIZE_N)) % N
    offset_K = tl.arange(0, BLOCK_SIZE_K)

    tl.assume(pid_m >= 0)
    tl.assume(pid_n >= 0)
    tl.assume(stride_xm > 0)
    tl.assume(stride_xk > 0)
    tl.assume(stride_yn > 0)
    tl.assume(stride_yk > 0)
    tl.assume(stride_om > 0)
    tl.assume(stride_on > 0)

    x_ptrs = x_ptr + (offset_X_m[:, None] * stride_xm + offset_K[None, :] * stride_xk)
    y_ptrs = y_ptr + (offset_K[:, None] * stride_yk + offset_Y_n[None, :] * stride_yn)

    accumulator = tl.zeros((BLOCK_SIZE_M, BLOCK_SIZE_N), dtype=tl.float32)
    for k in range(0, tl.cdiv(K, BLOCK_SIZE_K)):
        x = tl.load(x_ptrs, mask=offset_K[None, :] < K - k * BLOCK_SIZE_K, other=0.0)
        y = tl.load(y_ptrs, mask=offset_K[:, None] < K - k * BLOCK_SIZE_K, other=0.0)
        accumulator = tl.dot(x, y, accumulator)
        x_ptrs += BLOCK_SIZE_K * stride_xk
        y_ptrs += BLOCK_SIZE_K * stride_yk

    out = accumulator

    offset_om = pid_m * BLOCK_SIZE_M + tl.arange(0, BLOCK_SIZE_M)
    offset_on = pid_n * BLOCK_SIZE_N + tl.arange(0, BLOCK_SIZE_N)
    o_ptrs = o_ptr + offset_om[:, None] * stride_om + offset_on[None, :] * stride_on
    mask = (offset_om[:, None] < M) & (offset_on[None, :] < N)

    tl.store(o_ptrs, out, mask=mask)


def simple_triton_matmul(input_tensors: List[torch.Tensor]):
    x = input_tensors[0]
    y = input_tensors[1]

    M, K = x.shape
    K, N = y.shape

    out = torch.empty((M, N), device=x.device, dtype=x.dtype)
    grid = lambda META: (triton.cdiv(M, META['BLOCK_SIZE_M']) * triton.cdiv(N, META['BLOCK_SIZE_N']), )
    print(grid({"BLOCK_SIZE_M": 32, "BLOCK_SIZE_N": 32}))
    simple_matmul_kernel[grid](
        x, y, out,
        M, N, K,
        x.stride(0), x.stride(1),
        y.stride(0), y.stride(1),
        out.stride(0), out.stride(1),
        32, 32, 32, 32
    )

def torch_matmul(input_tensors: List[torch.Tensor]):
    x = input_tensors[0]
    y = input_tensors[1]

    return torch.matmul(x, y)

def make_tensor(size, device, dtype):
    m = size[0]
    k = size[1]
    n = size[2]

    x = torch.rand((m, k), device=device, dtype=dtype)
    y = torch.rand((k, n), device=device, dtype=dtype)

    return [x, y]

run_bench(simple_triton_matmul, torch_matmul, make_tensor, dtype=torch.float32, plot_name='matmul')
