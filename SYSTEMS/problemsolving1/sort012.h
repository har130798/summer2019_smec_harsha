//
// Created by harsha on 2019-05-25.
//

#ifndef DAY1_SORT012_H
#define DAY1_SORT012_H

#include "arrays.h"

int * sort012(int * arr, int len) {
    int i;
    int counts[3] = {0, 0, 0};
    for (i = 0; i < len; i++) {
        counts[arr[i]]++;
    }
    int * new_array = create_zeroed_array(len);
    for (i = len - 1; counts[2]; i--, counts[2]--) {
        new_array[i] = 2;
    }
    for (;counts[1]; i--, counts[1]--) {
        new_array[i] = 1;
    }
    return new_array;
}

#endif //DAY1_SORT012_H
