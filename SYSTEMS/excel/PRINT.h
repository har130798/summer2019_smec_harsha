//
// Created by harsha on 2019-05-27.
//

#ifndef EXCEL_PRINT_H
#define EXCEL_PRINT_H

#include "state.h"
#include "utils.h"
#include "GET.h"

void print(cell *** state);
char * valueOfCell(cell ***sheet, int i, int j);

#endif //EXCEL_PRINT_H
