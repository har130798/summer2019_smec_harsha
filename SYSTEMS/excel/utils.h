//
// Created by harsha on 2019-05-27.
//

#ifndef EXCEL_UTILS_H
#define EXCEL_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//FILE IO
FILE * open_file(char * filename, char * mode);
void close_file(FILE * f);
int compareStringsCaseInsensitive(char * a, char * b);

//GRID
char *** create_grid(int rows, int cols);
void print_grid(int ** grid, int rows, int cols);
//string
char * create_string(int len);
char * trim(char * input);
int get_number_from_start_till_end(char * input, int start);
char * reverse_string(char * s);
char * toString(int n);
int hasAlpha(char * s);

#endif //EXCEL_UTILS_H
