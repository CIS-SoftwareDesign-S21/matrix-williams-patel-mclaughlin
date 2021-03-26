#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mat.h"

int main(void) {
    int MAT_SIZE = 1000;
    for(int i = 10; i <= MAT_SIZE; i = i + 10){
        double *a = gen_matrix(i, i);
        double *b = gen_matrix(i, i);
        double *c_calc = malloc(i * i * sizeof(double));
        clock_t start;
        clock_t end;
        double cpu_time_used;
        start = clock();
        mmult(c_calc, a, i, i, b, i, i);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d, %f\n", i, cpu_time_used);
        free(a);
        free(b);
        free(c_calc);
    }
    
}
