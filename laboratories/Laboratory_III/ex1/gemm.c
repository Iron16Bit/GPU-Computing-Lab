#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "include/my_time_lib.h"

unsigned long long int matrix_multiplication(unsigned long long int n, double *A, double *B, double *C, unsigned long long int block_iter, unsigned long long int block_size) {
    unsigned long long int operations = 0;
    unsigned long long int offset = block_iter * block_size * block_size;

    for (unsigned long long int i = 0; i < block_size; i++) {
        for (unsigned long long int j = 0; j < block_size; j++) {
            double sum = 0.0;
            for (unsigned long long int k = 0; k < block_size; k++) {
                sum += A[offset + i * block_size + k] * B[offset + k * block_size + j];
                operations += 3;
            }
            C[offset + i * block_size + j] = sum;
        }
    }

    return operations;
}

unsigned long long int best_block(unsigned long long int n) {
    for (unsigned long long int i=n-1; i>=0; i--) {
        if (n%i == 0) {
            return i;
        }
    }
}

void print_matrix(double *C, unsigned long long int n) {
    for (unsigned long long int i=0; i<n; i++) {
        for (unsigned long long int j=0; j<n; j++) {
            printf("%f ", C[i * n + j]);
        }
        printf("\n");
    }
    printf("\n");
}

unsigned long long int main(unsigned long long int argc, char *argv[]) {

    if (argc != 2) {
        printf("Use ./gemm n\n");
        return -1;
    }
    unsigned long long int n = atoi(argv[1]);
    n = (int)pow(2, n);

    double *A = malloc(n * n * sizeof(double));
    double *B = malloc(n * n * sizeof(double));
    double *C = malloc(n * n * sizeof(double));

    srand(time(NULL));

    for (unsigned long long int i=0; i<n*n; i++) {
        A[i] = (double)rand();
        B[i] = (double)rand();
        C[i] = 0.0;
    }

    unsigned long long int block_size = best_block(n);
    printf("Block Size = %lld\n", block_size);
    unsigned long long int flops = 0;

    TIMER_DEF(a);
    TIMER_START(a);
    for (unsigned long long int i=0; i<(n/block_size); i++) {
        flops += matrix_multiplication(n, A, B, C, i, block_size);
    }
    TIMER_STOP(a);
    printf("Timer Elapsed: %f\n", TIMER_ELAPSED(a));
    printf("FLOPS: %lld\n", flops);
    printf("FLOPS/S = %f\n", ((double)flops)/TIMER_ELAPSED(a));

    return 0;
}