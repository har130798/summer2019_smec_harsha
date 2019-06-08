//
// Created by harsha on 2019-05-25.
//

#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdio.h>
#include <stdlib.h>

int * create_zeroed_array(int len) {
    int i;
    int * arr = (int *)malloc(sizeof(int) * len);
    for(i = 0; i < len; i++) {
        arr[i] = 0;
    }
    return arr;
}

int * input_array(int len) {
    int i;
    int * arr = (int *)malloc(sizeof(int) * len);
    for(i = 0; i < len; i++) {
        scanf("%d", &arr[i]);
    }
    return arr;
}

void print_array(int * arr, int len) {
    int i;
    for (i = 0; i < len; i ++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int * copy_array(int * arr, int len) {
    int * copy = (int *)malloc(sizeof(int) * len);
    int i;
    for (i = 0; i < len; i++) {
        copy[i] = arr[i];
    }
    return copy;
}

int ** allocate_2d_array(int m, int n) {
    int init_val = 0, i, j;
    int ** mat = (int **)malloc(sizeof(int *) * m);
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

int * create_filled_array(int len) {
    int * arr = (int *)malloc(sizeof(int) * len);
    int i;
    for (i = 0; i < len; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

#endif //ARRAYS_H
