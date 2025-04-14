#include <iostream>
#include <cstdlib>
#include <ctime>

#define dtype float

__global__
void sum_type2(dtype* a, dtype* b, int N) {
    for (int i=0; i<N/(blockDim.x*gridDim.x); i++) {
        int offset = i * (blockDim.x * gridDim.x) + threadIdx.x;
        if (offset < N) {
            a[offset] = a[offset] + b[offset];
        }
    }
}

__global__
void sum_type1(dtype* a, dtype* b, int N) {
    for (int i=0; i<N; i+=(blockDim.x*gridDim.x)) {
        int offset = (blockIdx.x * blockDim.x) + threadIdx.x;
        if (i + offset < N) {
            a[i + offset] = a[i + offset] + b[i + offset];
        }
    }
}

int main(void) {
    srand(time(NULL));

    // Allocate arrays in CPU
    int N = 4096*1000;
    dtype* a = (dtype*)malloc(N*sizeof(dtype));
    dtype* b = (dtype*)malloc(N*sizeof(dtype));
    for (int i=0; i<N; i++) {
        a[i] = (dtype)(rand()%2);
        b[i] = (dtype)(rand()%2);
    }

    // Move them to the GPU
    dtype* device_a;
    dtype* device_b;
    cudaMallocManaged(&device_a, N*sizeof(dtype));
    cudaMallocManaged(&device_b, N*sizeof(dtype));
    
    // Call GPU function
    int grid_size[] = {1, 3, 7, 14, 28, 56};
    int grids = 6;
    int block_size[] = {32, 64, 128, 256, 512, 1024};
    int blocks = 6;

    float linear_times[6][6];
    float consecutive_times[6][6];

    for (int i=0; i<grids; i++) {
        for (int j=0; j<blocks; j++) {
            cudaMemcpy(device_a, a, N*sizeof(dtype), cudaMemcpyHostToDevice);
            cudaMemcpy(device_b, b, N*sizeof(dtype), cudaMemcpyHostToDevice);

            cudaEvent_t start, stop;
            cudaEventCreate(&start);
            cudaEventCreate(&stop);

            cudaEventRecord(start);
            sum_type1<<<grid_size[i], block_size[j]>>>(device_a, device_b, N);
            cudaEventRecord(stop);
            cudaEventSynchronize(stop);

            cudaEventElapsedTime(&linear_times[i][j], start, stop);
        }
    }

    for (int i=0; i<grids; i++) {
        for (int j=0; j<blocks; j++) {
            cudaMemcpy(device_a, a, N*sizeof(dtype), cudaMemcpyHostToDevice);
            cudaMemcpy(device_b, b, N*sizeof(dtype), cudaMemcpyHostToDevice);

            cudaEvent_t start, stop;
            cudaEventCreate(&start);
            cudaEventCreate(&stop);

            cudaEventRecord(start);
            sum_type2<<<grid_size[i], block_size[j]>>>(device_a, device_b, N);
            cudaEventRecord(stop);
            cudaEventSynchronize(stop);

            cudaEventElapsedTime(&consecutive_times[i][j], start, stop);
        }
    }

    printf("Linear Access Times:\n");
    printf("\t\t1\t\t3\t\t7\t\t14\t\t28\t\t56\n");
    for (int i=0; i<6; i++) {
        printf("%d\t\t", block_size[i]);
        for (int j=0; j<6; j++) {
            printf("%f\t\t", linear_times[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Consecutive Access Times:\n");
    printf("\t\t1\t\t3\t\t7\t\t14\t\t28\t\t56\n");
    for (int i=0; i<6; i++) {
        printf("%d\t\t", block_size[i]);
        for (int j=0; j<6; j++) {
            printf("%f\t\t", consecutive_times[i][j]);
        }
        printf("\n");
    }

    // Free data
    cudaFree(device_a);
    cudaFree(device_b);
    free(a);
    free(b);
}
