#include <iostream>
#include <cstdlib>
#include <ctime>

#define dtype float

__global__
void sum(dtype* a, dtype* b, int N) {
    int th_per_bl = blockDim.x;
    for (int i=0; i<N/th_per_bl; i++) {
        if (i%2 == 0) {
            int offset = blockIdx.x * blockDim.x + threadIdx.x;
            if (i > 0) offset += 2*blockDim.x * (i-1);
            if (threadIdx.x == 2 && blockIdx.x == 1) printf("Thread %d is accessing %d at iteration %d\n", threadIdx.x, offset, i);
            if (offset < N/2) a[offset] = a[offset] + b[offset];
        } else {
            int offset = blockIdx.x * blockDim.x + threadIdx.x;
            offset += N/2;
            if (i > 1) offset += 2*blockDim.x * (i-2);
            if (threadIdx.x == 2 && blockIdx.x == 1) printf("Thread %d is accessing %d at iteration %d\n", threadIdx.x, offset, i);
            if (offset < N) a[offset] = a[offset] + b[offset];
        }
    }
}

int main(void) {
    srand(time(NULL));

    // Allocate arrays in CPU
    int N = 4096*10;
    dtype* a = (dtype*)malloc(N*sizeof(dtype));
    dtype* b = (dtype*)malloc(N*sizeof(dtype));
    for (int i=0; i<N; i++) {
        a[i] = (dtype)rand();
        b[i] = (dtype)rand();
    }

    // Move them to the GPU
    dtype* device_a;
    dtype* device_b;
    cudaMallocManaged(&device_a, N*sizeof(dtype));
    cudaMallocManaged(&device_b, N*sizeof(dtype));
    cudaMemcpy(device_a, a, N*sizeof(dtype), cudaMemcpyHostToDevice);
    cudaMemcpy(device_b, b, N*sizeof(dtype), cudaMemcpyHostToDevice);

    // Define timer
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Call GPU function
    int blocks = 2;
    int threads = 10;
    cudaEventRecord(start);
    sum<<<blocks, threads>>>(device_a, device_b, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    // Copy back the data
    cudaMemcpy(a, device_a, N*sizeof(dtype), cudaMemcpyDeviceToHost);

    // Get elapsed time
    float e_time = 0;
    cudaEventElapsedTime(&e_time, start, stop);
    printf("Kernel completed in %f ms\n", e_time);

    // Free data
    cudaFree(device_a);
    cudaFree(device_b);
    free(a);
    free(b);
}
