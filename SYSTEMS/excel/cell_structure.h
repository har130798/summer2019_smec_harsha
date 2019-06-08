//
// Created by harsha on 2019-05-27.
//

#ifndef EXCEL_CELL_STRUCTURE_H
#define EXCEL_CELL_STRUCTURE_H

#include <string.h>
#include <stdlib.h>
#include "utils.h"

typedef struct cell {
    char * val;
    char * expression;
}cell;

cell * create_cell(char * val, char * exp);
void delete_cell(cell * toDelete);
cell *** create_cell_grid();

#endif //EXCEL_CELL_STRUCTURE_H
