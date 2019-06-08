//
// Created by harsha on 2019-05-26.
//

#include "fiboMatrixExpo.h"
#include "arrays.h"

int ** multiply_matrix(int ** mat1, int ** mat2, int n) {
    int ** matrix = allocate_2d_array(n, n);
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int sum = 0;
            for (k = 0; k < n; k++) {
                sum += mat1[i][k] * mat2[k][j];
            }
            matrix[i][j] = sum;
        }
    }
    return matrix;
}

int ** matrix_exponent(int ** mat, int n, int p) {
    int ** newMat = multiply_matrix(matrix_exponent(mat, n, p / 2), matrix_exponent(mat, n, p / 2), n);
    if (p % 2 == 0) {
        return newMat;
    }
    else return multiply_matrix(newMat, mat, n);
}
