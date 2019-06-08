//
// Created by harsha on 2019-05-27.
//

#include "export.h"

void write_data_to_file(char * filename, int ** data) {
    if (filename == NULL) {
        printf("FILENAME NOT PROVIDED!");
        return;
    }
    FILE * f = open_file(filename, "w");

    char * cur = create_string(100);
    int i, j;
    for (i = 0; i < ROWS; i++) {
        int k = 0;
        cur[k++] = '\n';
        cur[k++] = '\r';
        for (j = COLUMNS - 1; j > -1; j--) {
            if (j != COLUMNS - 1) cur[k++] = ',';
            int num = data[i][j];
            do {
                cur[k++] = num % 10 + 48;
                num /= 10;
            }while (num);
        }
        cur[k] = 0;
        cur = reverse_string(cur);
        fprintf(f, "%s", cur);
    }
    close_file(f);
}