//
// Created by harsha on 2019-05-27.
//

#include "PRINT.h"

void print(cell *** sheet) {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            printf("%s ", valueOfCell(sheet, i, j)); //TODO SHOW FORMULA
        }
        printf("\n");
    }
}

char * valueOfCell(cell ***sheet, int i, int j) {
    char * arg = create_string(2);
    arg[0] = j + 65;
    arg[1] = i + 49;
    arg[2] = 0;
    char * val = get(sheet, arg);
    free(arg);
    arg = NULL;
    return val;
}
