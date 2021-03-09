#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mat.h"

#define MAT_SIZE 30

int test_unoptimized(double *a, int arows, int acols,
                     double *b, int brows, int bcols,
                     double *c_actual) {
        double *c_calc = malloc(MAT_SIZE * MAT_SIZE * sizeof(double));
    for(int i = 5; i <= MAT_SIZE; i++){
        clock_t start, end;
        start = clock();
        mmult(c_calc, a, i, i, b, i, i);
        end = clock();
        double time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("%i,%f\n", i, time_taken);
    }
    int are_same = compare_matrices(c_actual, c_calc, MAT_SIZE, MAT_SIZE);
    free(c_calc);
    return are_same;
}

int main(void) {
    double *a = read_matrix_from_file("a.txt");
    double *b = read_matrix_from_file("b.txt");
    double *c_actual = read_matrix_from_file("c.txt");
    double *c_calc = malloc(MAT_SIZE * MAT_SIZE * sizeof(double));

    if(!test_unoptimized(a, MAT_SIZE, MAT_SIZE, b, MAT_SIZE, MAT_SIZE, c_actual)) {
        exit(1);
    }

    puts("All tests pass.");

    free(a);
    free(b);
    free(c_actual);
}
