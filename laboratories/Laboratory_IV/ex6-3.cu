#include <iostream>
#include <cstdlib>
#include <ctime>

#define dtype float

__global__
void sum(dtype* a, dtype* b, int N) {
    for (int i=0; i<N/(blockDim.x*gridDim.x); i++) {
        int offset = i * (blockDim.x * gridDim.x) + threadIdx.x;
        if (offset < N) {
            a[offset] = a[offset] + b[offset];
        }
    }
}

int main(void) {
    srand(time(NULL));

    // Allocate arrays in CPU
    int N = 40;
    dtype* a = (dtype*)malloc(N*sizeof(dtype));
    dtype* b = (dtype*)malloc(N*sizeof(dtype));
    for (int i=0; i<N; i++) {
        a[i] = (dtype)(rand()%2);
        b[i] = (dtype)(rand()%2);
    }

    // printf("A: ");
    // for (int i=0; i<N; i++) {
    //     printf("%f ", a[i]);
    // }
    // printf("\n");
    // printf("B: ");
    // for (int i=0; i<N; i++) {
    //     printf("%f ", b[i]);
    // }
    // printf("\n");

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

    // printf("SUM: ");
    // for (int i=0; i<N; i++) {
    //     printf("%f ", a[i]);
    // }
    // printf("\n");

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
