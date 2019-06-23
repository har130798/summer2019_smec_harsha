//
// Created by harsha on 2019-05-26.
//

#ifndef FIBOMATRIXEXPO_H
#define FIBOMATRIXEXPO_H

#include <stdio.h>
#include <stdlib.h>

int ** allocate_2d_array(int m, int n) {
    int init_val = 0, i, j;
    int ** mat = (int **)malloc(sizeof(int **) * m);
    for (i = 0; i < m; i++) {
        mat[i] = (int *)malloc(sizeof(int) * n);
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j] = init_val;
        }
    }
    return mat;
}

void print_mat(int ** mat, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int ** input_mat(int m, int n) {
    int ** mat = allocate_2d_array(m, n);
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
    return mat;
}

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

int ** return_identity(int n) {
    int ** mat = allocate_2d_array(n, n);
    int i;
    for (i = 0; i < n; i++) {
        mat[i][i] = 1;
    }
    return mat;
}

int ** matrix_exponent(int ** mat, int n, int p) {
    if (p <= 0) {
        return return_identity(n);
    }
    int ** newMat = multiply_matrix(matrix_exponent(mat, n, p / 2), matrix_exponent(mat, n, p / 2), n);
    if (p % 2 == 0) {
        return newMat;
    }
    else return multiply_matrix(newMat, mat, n);
}

int nthFibo(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }
    n = n - 1;
    int ** mat = allocate_2d_array(2, 2);
    mat[0][0] = 0;
    mat[0][1] = 1;
    mat[1][0] = 1;
    mat[1][1] = 1;

    int ** out = matrix_exponent(mat, 2, n);

    return out[1][1];
}

#endif //DAY2_FIBOMATRIXEXPO_H
