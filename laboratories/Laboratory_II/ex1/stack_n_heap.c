#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define NPROBS 8

#define LEN 15
#define N 5
#define M 5


#define PRINT_RESULT_VECTOR( V, NAME ) {    \
    printf("%2s: ", NAME);                  \
    for (int i=0; i<LEN; i++)               \
        printf("%4d ", V[i]);               \
    printf("\n");                           \
}

#define PRINT_RESULT_MATRIX(MAT, NAME) {    \
    printf("%2s matrix:\n\t", NAME);        \
    for (int i=0; i<N; i++) {               \
        for (int j=0; j<M; j++)             \
            printf("%4d ", MAT[i*M+j]);     \
        printf("\n\t");                     \
    }                                       \
    printf("\n");                           \
}

// -------- uncomment these two lines when solutions are published --------
// #include "../../solutions/lab1_sol.cu"
// #define RESULTS
// ------------------------------------------------------------------------

#ifndef SOLUTION_STACKVEC_1
#define SOLUTION_STACKVEC_1 { }
#endif

#ifndef SOLUTION_HEAPVEC_1
#define SOLUTION_HEAPVEC_1 { }
#endif

#ifndef SOLUTION_HEAPVEC_2
#define SOLUTION_HEAPVEC_2 { }
#endif

#ifndef SOLUTION_STACKVEC_2
#define SOLUTION_STACKVEC_2 { }
#endif

#ifndef SOLUTION_STACKMAT_1
#define SOLUTION_STACKMAT_1 { }
#endif

#ifndef SOLUTION_HEAPMAT_1
#define SOLUTION_HEAPMAT_1 { }
#endif

#ifndef SOLUTION_HEAPMAT_2
#define SOLUTION_HEAPMAT_2 { }
#endif

#ifndef SOLUTION_STACKMAT_2
#define SOLUTION_STACKMAT_2 { }
#endif

int main(void) {
    // ---------- for timing ----------
    float CPU_times[NPROBS];
    for (int i=0; i<NPROBS; i++)
        CPU_times[i] = 0.0;
    struct timeval temp_1, temp_2;
    // --------------------------------

#ifdef RESULTS
    printf("You are now running the \x1B[31mSOLUTION CODE\x1B[37m:\n");
#else
    printf("You are now running \x1B[31mYOUR CODE\x1B[37m:\n");
#endif
    // ---------------------- Stack vectors 1 ----------------------
    /* Generate three stack vectors a, and b of length "LEN" such
     * that for each i in {0, 1, ... LEN-1} a[i] = i, b[i] = 100 * i.
     * Then compute the vector c = a + b.
     */

#ifdef RESULTS
        SOLUTION_STACKVEC_1
        PRINT_RESULT_VECTOR(c, "c")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */

        int a[LEN], b[LEN];
        for (int i=0; i<LEN; i++) {
            a[i] = i;
            b[i] = 100 * i;
        }
        int c[LEN];
        for (int i=0; i<LEN; i++) {
            c[i] = a[i] + b[i];
        }

        PRINT_RESULT_VECTOR(a, "a");
        PRINT_RESULT_VECTOR(b, "b");
        PRINT_RESULT_VECTOR(c, "c");


#endif
    // ---------------------- Heap vectors 1 -----------------------
    /* Compute the same result as c but in a heap vector c1 allocated
     * in the main but computed in a function out of the main.
     */
#ifdef RESULTS
    SOLUTION_HEAPVEC_1
    PRINT_RESULT_VECTOR(c1, "c1")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */

        int* c1 = (int*)malloc(LEN*sizeof(int));
        for (int i=0; i<LEN; i++) {
            c1[i] = a[i] + b[i];
        }
        PRINT_RESULT_VECTOR(c1, "c1");


#endif
    // ---------------------- Heap vectors 2 -----------------------
    /* Compute the same result as c and c1 in a heap vector c2
     * which, this time, is allocated in the function out of the main
     */
#ifdef RESULTS
    SOLUTION_HEAPVEC_2
    PRINT_RESULT_VECTOR(c2, "c2")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */


#endif
    // ---------------------- Stack vectors 2 ----------------------
    /* Is it possible to compute the c vector as a stack vector of
     * the out-main function and then return it to the main?
     */
#ifdef RESULTS
    SOLUTION_STACKVEC_2
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */


#endif


    /* Now, do the same 4 previous exercises but with the three
     * matrices A, B, C. All the matrices has N rows and M columns.
     * Moreover:
     *   1) A[i][j] = i + j
     *   2) B[i][j] = (i + j) * 100
     *   3) C = A + B
     *
     * What are the differences when you change from vectors to
     * matrices?
     */
    // --------------------- Stack matrices ----------------------
#ifdef RESULTS
        SOLUTION_STACKMAT_1
        PRINT_RESULT_MATRIX(((int*)C), "C")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */

        int A[N][M], B[N][M];
        for (int i=0; i<N; i++) {
            for (int j=0; j<M; j++) {
                A[i][j] = i+j;
                B[i][j] = (i+j)*100;
            }
        } 
        PRINT_RESULT_MATRIX(A, "A");
        PRINT_RESULT_MATRIX(B, "B");

        int C[N][M];
        for (int i=0; i<N; i++) {
            for (int j=0; j<M; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        PRINT_RESULT_MATRIX(C, "C");


#endif

    // --------------------- Heap matrices -----------------------
#ifdef RESULTS
        SOLUTION_HEAPMAT_1
        PRINT_RESULT_MATRIX(C1, "C1")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */

        int **C1 = (int **)malloc(N*sizeof(int));
        for (int i=0; i<N; i++) {
            C1[i] = (int *)malloc(M*sizeof(int));
            for (int j=0; j<M; j++) {
                C1[i][j] = A[i][j] + B[i][j];
            }
        }
        PRINT_RESULT_MATRIX(C1, "C1");


#endif

    // --------------------- Heap matrices -----------------------
#ifdef RESULTS
        SOLUTION_HEAPMAT_2
        PRINT_RESULT_MATRIX(C2, "C2")
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */


#endif

    // --------------------- Stack matrices ----------------------
#ifdef RESULTS
        SOLUTION_STACKMAT_2
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */


#endif

    for (int i=0; i<NPROBS; i++) {
        printf("Problem %d runs in %9.8f CPU time\n", i, CPU_times[i]);
    }
    printf("\n");

    return(0);
}
