#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void print_vec(int* v) {
    for (int i=0; i<10; i++) {
        printf("%d\t", v[i]);
    }
    printf("\n");
    fflush(stdout);
}

int main(void) {
    // Generate 3 random vectors of 10 elements
    srand(time(NULL));
    int a[10], b[10], c[10];
    for (int i=0; i<10; i++) {
        a[i] = (int)rand()%1000;
        b[i] = (int)rand()%1000;
        c[i] = (int)rand()%1000;
    }
    print_vec(a);
    print_vec(b);
    print_vec(c);

    // Compute mu and sigma
    double mu_a = 0, mu_b = 0, mu_c = 0;
    double sigma_a = 0, sigma_b = 0, sigma_c = 0;

    for (int i=0; i<10; i++) {
        mu_a += a[i];
        mu_b += b[i];
        mu_c += c[i];
    }
    mu_a /= 10;
    mu_b /= 10;
    mu_c /= 10;

    for (int i=0; i<10; i++) {
        sigma_a += pow((a[i] - mu_a), 2);
        sigma_b += pow((b[i] - mu_b), 2);
        sigma_c += pow((c[i] - mu_c), 2);
    }
    sigma_a /= 10;
    sigma_b /= 10;
    sigma_c /= 10;

    printf("mu_a: %f\tsigma_a: %f\n", mu_a, sigma_a);
    printf("mu_b: %f\tsigma_b: %f\n", mu_b, sigma_b);
    printf("mu_c: %f\tsigma_c: %f\n", mu_c, sigma_c);

    // Compute arithmetic and geometric mean
    double mu_am = 0;
    mu_am += mu_a + mu_b + mu_c;
    mu_am /= 3;
    
    double sigma_am = 0;
    sigma_am += sigma_a + sigma_b + sigma_c;
    sigma_am /= 10;

    double mu_gm = 0;
    mu_gm *= mu_a * mu_b * mu_c;
    mu_gm = pow(mu_gm, 1/3);

    double sigma_gm = 0;
    sigma_gm *= sigma_a * sigma_b * sigma_c;
    sigma_gm = pow(sigma_gm, 1/3);

    printf("mu_am: %f\tsigma_am: %f\n", mu_am, sigma_am);
    printf("mu_gm: %f\tsigma_gm: %f\n", mu_gm, sigma_gm);

    return 0;
}