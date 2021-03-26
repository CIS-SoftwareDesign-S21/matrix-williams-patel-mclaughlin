#include <stdio.h>
#include <stdlib.h>

#include "mat.h"

#define MAT_SIZE 5

int test_unoptimized(double *a, int arows, int acols,
                     double *b, int brows, int bcols,
                     double *c_actual) {
    double *c_calc = malloc(MAT_SIZE * MAT_SIZE * sizeof(double));

    mmult(c_calc, a, MAT_SIZE, MAT_SIZE, b, MAT_SIZE, MAT_SIZE);

    int are_same = compare_matrices(c_actual, c_calc, MAT_SIZE, MAT_SIZE);

    free(c_calc);

    return are_same;
}