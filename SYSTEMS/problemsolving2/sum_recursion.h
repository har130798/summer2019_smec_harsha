//
// Created by harsha on 2019-05-26.
//

#ifndef SUM_RECURSION_H
#define SUM_RECURSION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//long sum(int *, int);
long long fibonacci(int num, int * cache);
long long factorial(int num);
long long stairs(int n, int k, int * cache);
void print_n_digits(int n, int k, int * nums);
void print_calculator_inverse_n_digits(int n, int k, int * nums);
void print_calculator_number(int * nums, int len);
void print_permutations(int * arr, int len);

#endif //DAY2_SUM_RECURSION_H
