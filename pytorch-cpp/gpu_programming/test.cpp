// vector_addition.cpp
#include <hip/hip_runtime.h>
#include <iostream>

#define N 1024

__global__ void vector_add(const float* A, const float* B, float* C, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        C[idx] = A[idx] + B[idx];
    }
}

int main() {
    float *A, *B, *C;
    float *d_A, *d_B, *d_C;

    size_t size = N * sizeof(float);

    // Allocate host memory
    A = new float[N];
    B = new float[N];
    C = new float[N];

    // Initialize input vectors
    for (int i = 0; i < N; ++i) {
        A[i] = static_cast<float>(i);
        B[i] = static_cast<float>(i * 2);
    }

    // Allocate device memory
    hipMalloc(&d_A, size);
    hipMalloc(&d_B, size);
    hipMalloc(&d_C, size);

    // Copy data from host to device
    hipMemcpy(d_A, A, size, hipMemcpyHostToDevice);
    hipMemcpy(d_B, B, size, hipMemcpyHostToDevice);

    // Launch kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    hipLaunchKernelGGL(vector_add, dim3(blocksPerGrid), dim3(threadsPerBlock), 0, 0, d_A, d_B, d_C, N);

    // Copy result back to host
    hipMemcpy(C, d_C, size, hipMemcpyDeviceToHost);

    // Verify results
    bool success = true;
    for (int i = 0; i < N; ++i) {
        if (C[i] != A[i] + B[i]) {
            success = false;
            std::cerr << "Mismatch at index " << i << ": " << C[i] << " != " << A[i] + B[i] << "\n";
            break;
        }
    }

    if (success) {
        std::cout << "Vector addition succeeded.\n";
    }

    // Cleanup
    delete[] A;
    delete[] B;
    delete[] C;
    hipFree(d_A);
    hipFree(d_B);
    hipFree(d_C);

    return 0;
}
