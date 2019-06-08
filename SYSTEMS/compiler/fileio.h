//
// Created by harsha on 2019-06-01.
//

#ifndef COMPILER_FILEIO_H
#define COMPILER_FILEIO_H

#include <stdio.h>

char * readLine(FILE * fptr);

void close_file(FILE * f);
FILE * open_file(const char * name, const char * mode);

#endif //COMPILER_FILEIO_H
