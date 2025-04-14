#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "include/my_time_lib.h"

#define dtype int

double geometric_mean(double time[10]) {
    double retVal = 1.0;
    for (int i=0; i<10; i++) {
        retVal *= time[i] > 0.0 ? time[i] : 1.0;
    }
    return pow(retVal, 1.0/10.0);
}

int main(int argc, char *argv[]) {
    // SETUP
    if (argc != 3) {
        printf("USage: ./coo n m\n");
        return -1;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    srand(time(NULL));

    float p = 0.0;
    double time[2][10] = {0};

    for (int i=0; i<10; i++) {
        p += 0.1;

        dtype **A = malloc(n*sizeof(dtype*));
        for (int i=0; i<n; i++) {
            A[i] = malloc(m*sizeof(dtype));
            for (int j=0; j<m; j++) {
                float num = (rand()%100)/100.0;
                if (num > p) {
                    A[i][j] = (dtype)(rand()%10);
                } else {
                    A[i][j] = 0;
                }
            }
        }

        // MATRIX -> COO
        TIMER_DEF(a);
        TIMER_START(a);
        int non_null = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (A[i][j] != 0) {
                    non_null += 1;
                }
            }
        }

        int *Arow = malloc(non_null*sizeof(int));
        int *Acol = malloc(non_null*sizeof(int));
        dtype *Aval = malloc(non_null*sizeof(dtype));

        int counter = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (A[i][j] != 0) {
                    Arow[counter] = i;
                    Acol[counter] = j;
                    Aval[counter] = A[i][j];
                    counter += 1;
                }
            }
        }
        TIMER_STOP(a);

        // COO -> MATRIX
        TIMER_DEF(b);
        TIMER_START(b);
        dtype **B = malloc(n*sizeof(dtype*));
        for (int i=0; i<n; i++) {
            B[i] = malloc(m*sizeof(dtype));
            memset(B[i], 0, m*sizeof(dtype));
        }

        for(int i=0; i<non_null; i++) {
            B[Arow[i]][Acol[i]] = Aval[i];
        }
        TIMER_STOP(b);

        time[0][i] = TIMER_ELAPSED(a);
        time[1][i] = TIMER_ELAPSED(b);

    }

    printf("[MATRIX -> COO]\n");
    for (int i=0; i<10; i++) {
        printf("%f ", time[0][i]);
    }
    printf("\n\t=> %f\n\n", geometric_mean(time[0]));
    printf("[COO -> MATRIX]\n");
    for (int i=0; i<10; i++) {
        printf("%f ", time[1][i]);
    }
    printf("\n\t=> %f\n", geometric_mean(time[1]));

    return 0;
}