#include "fiboMatrixExpo.h"
#include "mergesort_dll.h"
//#include "arrays.h"
//#include "permuteWithReps.h"
#include "sum_recursion.h"

long long power2wayrecurse(int base, int exponent) {
    if (exponent == 0) {
        return 1;
    }
    long long answer = power2wayrecurse(base, exponent / 2) * power2wayrecurse(base, exponent / 2);
    return exponent % 2 != 0 ? answer * base : answer;
}
int * input_array(int len) {
    int i;
    int * arr = (int *)malloc(sizeof(int) * len);
    for(i = 0; i < len; i++) {
        scanf("%d", &arr[i]);
    }
    return arr;
}

int main() {
//    int ** a = input_mat(5, 5);
//    a = matrix_exponent(a, 2, 4);
//    print_mat(a, 2, 2);
//    char * s = (char *)malloc(sizeof(char ) * 25);
//    scanf("%s", s);
//    char ** a = input_char_array(5, 5, s);
//    char b[100];
//    scanf("%s", b);
//    get_pos_in_crossword(a, 5, 5, b);
//    int * a = input_array(4);
//    dll * m = make_dll(a, 5);
//    m = mergesort_dll(m);
//    printf("%d", nthFibo(21));
//    print_dll(m);
//    permute_array(a, 4);
    print_calculator_inverse_n_digits(4, 0, input_array(4));
    return 0;
}
