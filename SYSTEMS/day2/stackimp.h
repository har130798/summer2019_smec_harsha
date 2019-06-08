//
// Created by harsha on 2019-05-26.
//

#ifndef STACKIMP_H
#define STACKIMP_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct stack {
    int * arr;
    int top;
    int size;
}stack;

stack * create_stack(int length) {

    stack * s = (stack *)malloc(sizeof(stack));
    s->arr = (int *)malloc(sizeof(int) * length);
    s->top = -1;
    s->size = length;

    return s;
}

int push(stack * s, int el) {
    if (s->size == s->top + 1) {
        return -1;
    }

    s->arr[++(s->top)] = el;
    return s->top;
}

int peek(stack * s) {
    if (s->top == -1) {
        return -1;
    }
    return s->arr[s->top];
}

int pop(stack * s) {
    if (s->top == -1) {
        return -1;
    }

    return s->arr[s->top--];
}

bool isEmpty(stack * s) {
    return s->top == -1 ? true : false;
}


#endif //DAY2_STACKIMP_H
