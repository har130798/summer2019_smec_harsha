//
// Created by harsha on 2019-05-31.
//

#include "futils.h"
#include <stdlib.h>

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

void write_file(void * ptr, size_t size, size_t n_el, FILE * f){
    if (fwrite(ptr, size, n_el, f) == 0){
        printf("Error in writing to file!\n");
        exit(1);
    }
}

unsigned int getFilesize(char * file) {
    FILE * toRead = open_file(file, "rb");
    fseek(toRead,0,SEEK_END);

    unsigned int size=ftell(toRead);
    printf("%d\n", size);
    close_file(toRead);
    return size;
}