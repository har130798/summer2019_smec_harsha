//
// Created by harsha on 2019-05-26.
//

#include "crossword.h"

int * make_pair(int x, int y) {
    int * a = (int *)malloc(sizeof(int) * 2);
    a[0] = x, a[1] = y;
    return a;
}

int * traverse(char ** mat, int m, int n, int x, int y, int p, int q, char * s, char * target, int char_ind) {
    if (p < 0 || p > m - 1 || q < 0 || q >= n) {
        return make_pair(-1, -1);
    }
    s[char_ind++] = mat[p][q];
    if (target[char_ind] == 0) {
        s[char_ind] = 0;
        if (strcmp(s, target) == 0) {
            return make_pair(p, q);
        } else {
            return make_pair(-1, -1);
        }
    }
    int xdiff = x - p, ydiff = y - q;
    if (xdiff == 0 && ydiff == -1) {
        return traverse(mat, m, n, p, q, p, q + 1, s, target, char_ind);
    }
    if (xdiff == 0 && ydiff == 1) {
        return traverse(mat, m, n, p, q, p, q - 1, s, target, char_ind);
    }
    if (xdiff == -1 && ydiff == 0) {
        return traverse(mat, m, n, p, q, p + 1, q, s, target, char_ind);
    }
    if (xdiff == 1 && ydiff == 0) {
        return traverse(mat, m, n, p, q, p - 1, q, s, target, char_ind);
    }
    if (xdiff == -1 && ydiff == -1) {
        return traverse(mat, m, n, p, q, p + 1, q + 1, s, target, char_ind);
    }
    if (xdiff == 1 && ydiff == 1) {
        return traverse(mat, m, n, p, q, p - 1, q - 1, s, target, char_ind);
    }
    if (xdiff == -1 && ydiff == 1) {
        return traverse(mat, m, n, p, q, p + 1, q - 1, s, target, char_ind);
    }
    if (xdiff == 1 && ydiff == -1) {
        return traverse(mat, m, n, p, q, p - 1, q + 1, s, target, char_ind);
    }
}

void check_res(int x, int y, int * a) {
    if(a[0] == -1 && a[1] == -1) {
        return;
    }
    printf("[%d %d]  [%d %d]\n", x, y, a[0], a[1]);
}

void get_pos_in_crossword(char ** mat, int r, int c, char * target) {
    char * s = (char *)malloc(sizeof(char) * (strlen(target) + 1));
    int i, j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (mat[i][j] == target[0]) {
                s[0] = target[0];
                check_res(i, j, traverse(mat, r, c, i, j, i, j + 1, s, target, 1));
                check_res(i, j, traverse(mat, r, c, i, j, i, j - 1, s, target, 1));
                check_res(i, j, traverse(mat, r, c, i, j, i + 1, j, s, target, 1));
                check_res(i, j, traverse(mat, r, c, i, j, i - 1, j, s, target, 1));
                check_res(i, j, traverse(mat, r, c, i, j, i + 1, j + 1, s, target, 1));
                check_res(i, j, traverse(mat, r, c, i, j, i - 1, j - 1, s, target, 1));
                check_res(i, j, traverse(mat, r, c, i, j, i + 1, j - 1, s, target, 1));
                check_res(i, j, traverse(mat, r, c, i, j, i - 1, j + 1, s, target, 1));
            }
        }
    }
}

char ** input_char_array(int m, int n, char * s) {
    int i, j, k = 0;
    char ** mat = (char **)malloc(sizeof(char *) * m);
    for (i = 0; i < m; i++) {
        mat[i] = (char *)malloc(sizeof(char) * n);
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j] = s[k++];
        }
    }
    return mat;
}

void print_char_mat(char ** mat, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
}