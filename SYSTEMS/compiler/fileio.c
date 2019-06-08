//
// Created by harsha on 2019-06-01.
//

#include "fileio.h"

#include <stdio.h>
#include <string.h>
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

int readAllLines(const char * filename, char *** linesPtr) {
    char ** lines = (char **)malloc(sizeof(char *) * 1000);
    *(linesPtr) = lines;

    FILE * f = open_file(filename, "r");
    int i = 0;

    while(feof(f) == 0) {
        lines[i] = (char *)malloc(sizeof(char) * 100);
        fgets(lines[i++], 100, f);
//        printf("%s", lines[i - 1]);
    }

    close_file(f);
    return i;
}
