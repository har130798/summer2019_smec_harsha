//
// Created by harsha on 2019-05-28.
//

#ifndef EXCEL_MY_STACK_H
#define EXCEL_MY_STACK_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct stack {
    int * arr;
    int top;
    int size;
}stack;

stack * create_stack(int length);

int push(stack * s, int el);

int peek(stack * s);

int pop(stack * s);

bool isEmpty(stack * s);

#endif //EXCEL_MY_STACK_H
