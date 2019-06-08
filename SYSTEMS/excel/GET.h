//
// Created by harsha on 2019-05-27.
//

#ifndef EXCEL_GET_H
#define EXCEL_GET_H

#include "state.h"
#include "utils.h"
#include "linked_list_string.h"
#include "my_stack.h"

int evaluate_cell(cell *** sheet, char * arg);
char * get(cell *** state, const char * arg);
int convertToNumber(char *);
char * get_cell_position(char * s, int pos);
int get_number_position(char * s, int pos);


int getPrecedence(char c);
int isOperator(char c);
lls * toPostfix(char * infix);
int eval(int a, int b, char op);
int evaluatePostfix(lls * postfix, cell *** sheet);


#endif //EXCEL_GET_H
