#include <stdio.h>
#include "loopInLinkedList.h"
#include "sort01.h"
#include "border.h"
#include "addTwoLinkedLists.h"

void test_add_two_linked() {
    int a[10] = {9, 9, 9};
    int b[10] = {9, 9, 9};

    ll * al = init_list(a, 3);
    ll * bl = init_list(b, 3);

    print_list(al);
    print_list(bl);

//    ll * added = addTwoLinkedLists(al, bl);
//    print_list(added);
}

void test_sort01() {
    int a[10] = {0,1,2,1,2,2,1,2,1,1};
    int b[10] = {0,0,0,0,1,1,1,1,1,1};
    int c[10] = {0,0,0,0,0,0,0,0,0,0};
    int d[10] = {1,1,1,1,1,1,1,1,1,1};
    int e[10] = {1,1,1,1,1,0,0,0,0,0};

//    print_array(sort01_count_ones(a, 10), 10);
//    print_array(sort01_sort(a, 10), 10);
//    print_array(sort012(b, 10), 10);
//    print_array(sort01_2pointer(b, 10), 10);
//    print_array(sort01_2pointer(c, 10), 10);
//    print_array(sort01_2pointer(d, 10), 10);
//    print_array(sort01_2pointer(e, 10), 10);
}

void test_border() {
    int r = 4, c = 7;
    int ** m = input_mat(r, c);
    int * a = create_zeroed_array(r * c);
    print_array(a, r * c);
//    collect_border(m, 0, r, 0, c, a, 0);
    collect_border_iterative(m, r, c, a);
    print_array(a, r * c);
}

int main() {
    int * arr1 = input_array(6);
    int * arr2 = input_array(4);

    ll * l1 = init_list(arr1, 6);
    ll * l2 = init_list(arr2, 4);

    ll * n = addTwoLinkedLists(l1, l2);

    print_list(n);

    return 0;
}