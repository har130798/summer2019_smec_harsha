//
// Created by harsha on 2019-05-25.
//

#ifndef DAY1_SORT01_H
#define DAY1_SORT01_H

#include "arrays.h"

int * sort01_count_ones(int * arr, int len) {
    int i, sum = 0;
    int * new_arr = create_zeroed_array(len);
    for(i = 0; i < len; i++) {
        sum += arr[i];
    }
    for (i = len - 1; sum > 0; i--) {
        new_arr[i] = 1;
        sum--;
    }
    return new_arr;
}

int compare(void * a, void * b) {
    return *((int *)a) - *((int *)b);
}

int * sort01_sort(int * arr, int len) {
    qsort(arr, len, sizeof(int), compare);
    return copy_array(arr, len);
}

int * sort01_2pointer(int * arr, int len) {
    int left = 0, right = len - 1;
    while(left < right) {
        while(left < len) {
            if(arr[left] == 1) break;
            left++;
        }
        while(right >= 0) {
            if(arr[right] == 0) break;
            right--;
        }
        if (left < right) {
            arr[left++] = 0;
            arr[right--] = 1;
        }
    }
    return arr;
}
#endif //DAY1_SORT01_H
