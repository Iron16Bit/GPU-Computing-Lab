#include <stdio.h>
#include <stdlib.h>

__global__ void print_from_gpu(void) {
    printf("I'm worker %d from block %d\n", threadIdx.x, blockIdx.x);
}

int main(void) {
    printf("Hello from host!\n");
    print_from_gpu<<<1,1>>>();
    cudaDeviceSynchronize();
    return 0;
}