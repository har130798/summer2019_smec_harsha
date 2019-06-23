//
// Created by harsha on 2019-05-31.
//

#ifndef FSYSTEM_EXT_UTILS_H
#define FSYSTEM_EXT_UTILS_H

#include <stdio.h>

void close_file(FILE * f);
FILE * open_file(const char * name, const char * mode);
void write_file(void * ptr, size_t size, size_t n_el, FILE * f);
unsigned int getFilesize(char * file);
char * readLine(FILE * fptr);

#endif //FSYSTEM_EXT_UTILS_H
