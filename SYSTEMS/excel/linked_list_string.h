//
// Created by harsha on 2019-05-28.
//

#ifndef EXCEL_LINKED_LIST_STRING_H
#define EXCEL_LINKED_LIST_STRING_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lls {
    char * val;
    struct lls * next;
}lls;

lls * create_node(char * val);

void delete_list(lls * node);

void print_list(lls * node);

lls * init_list(char ** arr, int len);

int get_ll_length(lls * node);

#endif //EXCEL_LINKED_LIST_STRING_H
