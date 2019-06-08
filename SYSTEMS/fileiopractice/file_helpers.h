//
// Created by harsha on 2019-05-26.
//

#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

#include <stdio.h>
#include <stdlib.h>

void close_file(FILE * f);
FILE * open_file(const char * name, const char * mode);

#endif //FILEIOPRACTICE_FILE_HELPERS_H
