//
// Created by harsha on 2019-05-26.
//

#include "file_helpers.h"

void close_file(FILE * f) {
    fclose(f);
    f = NULL;
}

FILE * open_file(const char * name, const char * mode) {
    FILE * f;
    if ((f = fopen(name, mode)) == NULL) {
        printf("File open error\nName : %s , Mode : %s\n", name, mode);
        exit(1);
    }
    return f;
}

