//
// Created by harsha on 2019-05-26.
//

#ifndef DAY2_CROSSWORD_H
#define DAY2_CROSSWORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_char_mat(char ** mat, int m, int n);
char ** input_char_array(int m, int n, char * s);
void get_pos_in_crossword(char ** mat, int r, int c, char * target);

#endif //DAY2_CROSSWORD_H
