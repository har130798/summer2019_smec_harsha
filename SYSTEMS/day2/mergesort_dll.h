//
// Created by harsha on 2019-05-26.
//

#ifndef MERGESORT_DLL_H
#define MERGESORT_DLL_H


#include <stdio.h>
#include <stdlib.h>

typedef struct dll {
    int val;
    struct dll * next;
    struct dll * prev;
}dll;

dll * mergesort_dll(dll * head);
dll * merge(dll *, dll *);
dll * make_dll(int *, int);
void print_dll(dll *);

#endif //DAY2_MERGESORT_DLL_H
