//
// Created by harsha on 2019-05-25.
//

#ifndef DAY1_BORDER_H
#define DAY1_BORDER_H
#include<stdio.h>
#include<stdlib.h>
#include "arrays.h"

void collect_border(int ** mat, int rs, int re, int cs, int ce, int * arr, int cur_index) {
    if (rs >= re || cs >= ce) {
        return;
    }
    int numToCopy = (re - rs) * (ce - cs);
    int i;
    int ind = cur_index;

    for (i = cs; i < ce && numToCopy; i++) { //right
        arr[ind++] = mat[rs][i];
        numToCopy--;
    }
    for (i = rs + 1; i < re && numToCopy; i++) { //down
        arr[ind++] = mat[i][ce - 1];
        numToCopy--;
    }
    for (i = ce - 2; i >= cs && numToCopy; i--) { //left
        arr[ind++] = mat[re - 1][i];
        numToCopy--;
    }
    for (i = re - 2; i >= rs + 1 && numToCopy; i--) { //up
        arr[ind++] = mat[i][cs];
        numToCopy--;
    }

    return collect_border(mat, rs + 1, re - 1, cs + 1, ce - 1, arr, ind);
}

void collect_border_iterative(int ** mat, int m, int n, int * arr) {
    int rs = 0, re = m, cs = 0, ce = n;
    int cur_index = 0;
    while(rs < re && cs < ce) {
        int numToCopy = (re - rs) * (ce - cs);
        int i;
        int ind = cur_index;

        for (i = cs; i < ce && numToCopy; i++) { //right
            arr[ind++] = mat[rs][i];
            numToCopy--;
        }
        for (i = rs + 1; i < re && numToCopy; i++) { //down
            arr[ind++] = mat[i][ce - 1];
            numToCopy--;
        }
        for (i = ce - 2; i >= cs && numToCopy; i--) { //left
            arr[ind++] = mat[re - 1][i];
            numToCopy--;
        }
        for (i = re - 2; i >= rs + 1 && numToCopy; i--) { //up
            arr[ind++] = mat[i][cs];
            numToCopy--;
        }

        cur_index = ind;
        rs++;
        re--;
        cs++;
        ce--;
    }
}
#endif //DAY1_BORDER_H
