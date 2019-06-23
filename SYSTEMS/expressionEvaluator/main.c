#include <stdio.h>
#include <stdlib.h>
#include "expressionEval.h"

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

int solve (int ** maze, int m, int n, int sx, int sy, int ex, int ey, int ** path, int k) {
    if (sx == ex && sy == ey) {
        return k;
    }
    if (sx >= m || sx < 0 || sy < 0 || sy >= n || maze[sx][sy] < 1) return 0;

    maze[sx][sy] = -1;

    path[k][0] = sx;
    path[k][1] = sy - 1;
    int ans;
    if ((ans = solve(maze, m, n, sx, sy - 1, ex, ey, path, k + 1)) > 0)
        return ans;
    path[k][0] = sx;
    path[k][1] = sy + 1;
    if ((ans = solve(maze, m, n, sx, sy + 1, ex, ey, path, k + 1)) > 0)
        return ans;
    path[k][0] = sx + 1;
    path[k][1] = sy;
    if ((ans = solve(maze, m, n, sx + 1, sy, ex, ey, path, k + 1)) > 0)
        return ans;
    path[k][0] = sx - 1;
    path[k][1] = sy;
    if ((ans = solve(maze, m, n, sx - 1, sy, ex, ey, path, k + 1)) > 0)
        return ans;

    return -1;
}

//solve maze input: maze, start and end
void solve_maze(int ** maze, int m, int n, int sx, int sy, int ex, int ey) {
    //allocate path matrix
    //call solve
    int ** path = allocate_2d_array(m * n, 2);
    path[0][0] = sx;
    path[0][1] = sy;

    int k = solve(maze, m, n, sx, sy, ex, ey, path, 1);

    if (k > 1) print_mat(path, k, 2);
    else printf("No path available\n");

}

int main() {
    char * s = (char *)malloc(sizeof(char) * 100);
    scanf("%s", s);
    lls * m = toPostfix(s);
    print_list(m);
    printf("%d\n", evaluatePostfix(m));
}