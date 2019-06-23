//
// Created by harsha on 2019-05-31.
//

//
// Created by harsha on 2019-05-30.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_SIZE 100

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

char * readLine(FILE * fptr) {
    int i = 0;
    char c;
    char * line = (char *)malloc(sizeof(char) * MAX_LINE_SIZE);

    return fgets(line, MAX_LINE_SIZE, fptr);
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
