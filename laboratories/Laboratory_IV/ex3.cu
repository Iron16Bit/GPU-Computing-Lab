#include <iostream>
#include <cstdlib>
#include <ctime>

__global__
void sum(float* a, float* b) {
    a[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
}

int main(void) {
    srand(time(NULL));

    // Allocate arrays in CPU
    int N = 4096;
    float* a = (float*)malloc(N*sizeof(float));
    float* b = (float*)malloc(N*sizeof(float));
    for (int i=0; i<N; i++) {
        a[i] = (float)rand();
        b[i] = (float)rand();
    }

    // Move them to the GPU
    float* device_a;
    float* device_b;
    cudaMallocManaged(&device_a, N*sizeof(float));
    cudaMallocManaged(&device_b, N*sizeof(float));
    cudaMemcpy(device_a, a, N*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(device_b, b, N*sizeof(float), cudaMemcpyHostToDevice);

    // Define timer
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Call GPU function
    cudaEventRecord(start);
    sum<<<1, N>>>(device_a, device_b);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    // Copy back the data
    cudaMemcpy(a, device_a, N*sizeof(float), cudaMemcpyDeviceToHost);

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