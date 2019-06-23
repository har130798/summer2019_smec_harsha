//
// Created by harsha on 2019-05-26.
//

#include "permuteWithReps.h"

int * remove_number(int * arr, int len, int toRemove) {
    int * new_arr = (int *)malloc(sizeof(int) * (len - 1));
    int seen = 0;
    int i, k = 0;

    for (i = 0; i < len; i++) {
        if (!seen && arr[i] == toRemove) {
            seen = 1;
            continue;
        }
        new_arr[k++] = arr[i];
    }

    return new_arr;
}

int * add_number(int * arr, int len, int toAdd) {
    int * newArr = (int *)malloc(sizeof(int) * (len + 1));
    int i, k = 0;
    for (i = 0; i < len; i++) {
        if (arr[i] <= toAdd) {
            newArr[k++] = arr[i];
        } else {
            newArr[k++] = toAdd;
            break;
        }
    }
    for (; i < len; i++) {
        newArr[k++] = arr[i];
    }
    return newArr;
}

void print_formed_number(int * nums, int len) {
    int i, num = 0;
    for (i = 0; i < len; i++) {
        num = num * 10 + nums[i];
    }
    printf("%d\n", num);
}

void permuteWithReps(int * available, int avail_len, int * chosen, int chose_len) {
    if (avail_len == 0) {
        print_formed_number(chosen, chose_len);
        return;
    }
    int i;
    for (i = 0; i < avail_len; i++) {
        int current = available[i];
        chosen[chose_len] = current;
        if (i != 0 && available[i - 1] == current) continue;
        permuteWithReps(
                remove_number(available, avail_len, current),
                avail_len - 1,
                chosen,
                chose_len + 1
                );
    }
}

int comparator(const void * a, const void * b) {
    return *((int *)a) - *((int *)b);
}

void permute_array(int * input, int len) {
    int * ch = (int *)malloc(sizeof(int) * len);
    qsort(input, len, sizeof(int), comparator);
    permuteWithReps(input, len, ch, 0);
}

