#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main() {
    double a[150][150], b[150][150], c[150][150];
    int i, j, k;
    for (i = 0; i < 150; i++) {
        for (j = 0; j < 150; j++) {
            a[i][j] = 1.1;
            b[i][j] = 1.1;
            c[i][j] = 1.1;
        }
    }
    printf("20BCE0959\n");
    printf("Serial\n");
    double t1 = omp_get_wtime();
    for (i = 0; i < 150; i++) {
        for (j = 0; j < 150; j++) {
            for (k = 0; k < 150; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    double t2 = omp_get_wtime();
    printf("Serial Time %f\n", t2 - t1);
    printf("Parallel\n");
    t1 = omp_get_wtime();
    #pragma omp parallel for private(i, j, k)
    for (i = 0; i < 150; i++) {
        for (j = 0; j < 150; j++) {
            for (k = 0; k < 150; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    t2 = omp_get_wtime();
    printf("Parallel Time: %f\n", t2 - t1);
    return 0;
}
