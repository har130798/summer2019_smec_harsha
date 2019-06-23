//
// Created by harsha on 2019-05-25.
//

#ifndef DAY1_TRANSPOSE_H
#define DAY1_TRANSPOSE_H

#include "arrays.h"

int ** transpose(int ** mat, int m, int n) {
    int ** newmat = allocate_2d_array(n, m);
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            newmat[j][i] = mat[i][j];
        }
    }
    return newmat;
}

#endif //DAY1_TRANSPOSE_H
