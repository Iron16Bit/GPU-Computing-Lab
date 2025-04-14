#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// #include <cblas.h>
#include "include/my_time_lib.h"

void print_matrix(double **C, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%f ", C[i][j]);
        }
        printf("\n");
    }
}

void matrix_multiplication(int n, double **A, double **B, double **C) {
    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            double tmp = 0;
            for (int j=0; j<n; j++) {
                tmp += A[i][j] * B[j][i];
            }
            C[k][i] = tmp;
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Use ./gemm n\n");
        return -1;
    }
    int n = atoi(argv[1]);
    n = (int)pow(2, n);

    double **A = malloc(n * sizeof(double*));
    double **B = malloc(n * sizeof(double*));
    double **C1 = malloc(n * sizeof(double*));
    double **C2 = malloc(n * sizeof(double*));
    for (int i = 0; i < n; ++i) {
        A[i] = malloc(n * sizeof(double));
        B[i] = malloc(n * sizeof(double));
        C1[i] = malloc(n * sizeof(double));
        C2[i] = malloc(n * sizeof(double));
    }

    srand(time(NULL));

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            A[i][j] = (double)rand();
            B[i][j] = (double)rand();
            C1[i][j] = 0.0;
            C2[i][j] = 0.0;
        }
    }

    // Perform C = A * B using BLAS
    // TIMER_DEF(oblas_var);
    // TIMER_START(oblas_var);
    // cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
    //     n, n, n, 1.0, (const double*)&A, n, (const double*)&B, n, 0.0, (double*)&C1, n);
    // TIMER_STOP(oblas_var);
    // printf("[OpenBLAS]\n");
    // printf("Elapsed time: %f\n", TIMER_ELAPSED(oblas_var));

    // Perform C = A * B using your own function
    TIMER_DEF(my_var);
    TIMER_START(my_var);
    matrix_multiplication(n, A, B, C2);
    TIMER_STOP(my_var);
    printf("[My result]\n");
    printf("Elapsed time: %f\n", TIMER_ELAPSED(my_var));


    return 0;
}
