#include <stdio.h>
#include <omp.h>
int akm(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
    	int ans;
        #pragma omp task shared(ans)
        ans = akm(m - 1, 1);
        #pragma omp taskwait
        return ans;
    } else {
        int n_val;
        int anns;
        #pragma omp task shared(n_val)
        n_val = akm(m, n - 1);
        #pragma omp taskwait
        #pragma omp task shared(anns)
        anns = akm(m - 1, n_val);
        #pragma omp taskwait
        return anns;
    }
}
int main(int *arg,char *argv[]) {
    int m, n;
    printf("Enter m and n: ");
    scanf("%d %d", &m, &n);
    printf("20BCE0959\n");
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Ackermann(%d, %d) = %d\n", m, n, akm(m, n));
        }
    }
    return 0;
}