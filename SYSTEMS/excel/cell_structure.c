//
// Created by harsha on 2019-05-27.
//

#include "cell_structure.h"

cell * create_cell(char * val, char * exp) {
    cell * new_cell = (cell *)malloc(sizeof(cell));
    if (exp != NULL) {
        new_cell->expression = create_string(strlen(exp));
        strcpy(new_cell->expression, exp);
    } else {
        int val_len = val != NULL ? strlen(val) : 0;
        new_cell->val = create_string(1000);
        strcpy(new_cell->val, val_len == 0 ? "0" : val);
        new_cell->expression = NULL;
    }
    return new_cell;
}

void delete_cell(cell * toDelete) {
    free(toDelete);
    toDelete = NULL;
}

cell *** create_cell_grid() {
    int i, j;
    cell *** grid = (cell ***)malloc(sizeof(cell **) * 10);
    for (i = 0; i < 10; i++) {
        grid[i] = (cell **)malloc(sizeof(cell*) * 10);
        for (j = 0; j < 10; j++) {
            grid[i][j] = create_cell(0, NULL);
        }
    }
    return grid;
}



