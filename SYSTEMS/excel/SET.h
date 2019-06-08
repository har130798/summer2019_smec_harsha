//
// Created by harsha on 2019-05-27.
//

#ifndef EXCEL_SET_H
#define EXCEL_SET_H

#include "state.h"
#include "utils.h"
#include <string.h>

void set(cell *** sheet, char * args);
void parse_set_argument(char * arg, cell * toCopyInto);
int isNumberSubString(char * s, int , int );
int isAlphaSubString(char * s, int , int);
int copySubString(char * dest, const char * src, int start, int end);

#endif //EXCEL_SET_H
