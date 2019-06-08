//
// Created by harsha on 2019-05-31.
//

#ifndef DAY7FS_FUTILS_H
#define DAY7FS_FUTILS_H

#include <stdio.h>

void close_file(FILE * f);
FILE * open_file(const char * name, const char * mode);
void write_file(void * ptr, size_t size, size_t n_el, FILE * f);
unsigned int getFilesize(char * filename);

#endif //DAY7FS_FUTILS_H
