//
// Created by harsha on 2019-05-26.
//

#include "sum_recursion.h"

long long factorial(int num) {
    return num > 1 ? num * factorial(num - 1) : 1;
}

long long fibonacci(int num, int * cache) {
    if (num <= 0) {
        return 0;
    } else if (num == 1) {
        cache[num] = 1;
        return 1;
    }
    if (cache[num] != 0) return cache[num];
    cache[num] = fibonacci(num - 1, cache) + fibonacci(num - 2, cache);
    return cache[num];
}

long long stairs(int n, int k, int * cache) {
    if (n == 0) {
        cache[n] = 1;
        return 1;
    }
    if (n < 0) return 0;

    if (cache[n] != 0) return cache[n];
    int i, ways = 0;
    for (i = 1; i <= k; i++) {
        ways += stairs(n - i, k, cache);
    }
    cache[n] = ways;
    return ways;
}

void print_number(int * nums, int len) {
    int i, num = 0;
    for (i = 0; i < len; i++) {
        num = num * 10 + nums[i];
    }
    printf("%d\n", num);
}

void print_n_digits(int n, int k, int * nums) {
    if (k >= n - 1) {
        print_number(nums, k);
        return;
    }
    int i;
    for (i = 0; i < 10; i++) {
        nums[k] = i;
        print_n_digits(n, k + 1, nums);
    }
}

void print_calculator_number(int * nums, int len) {
    char map[10] = "012Eh59L86";
    int i, num = 0;
    for (i = 0; i < len; i++) {
        num = num * 10 + nums[i];
    }

    do {
        printf("%c", map[num % 10]);
        num /=  10;
    } while(num > 0);
    printf("\n");
}

void print_calculator_inverse_n_digits(int n, int k, int * nums) {
    if (k >= n - 1) {
        print_calculator_number(nums, k);
        return;
    }
    int i;
    for (i = 0; i < 10; i++) {
        nums[k] = i;
        print_calculator_inverse_n_digits(n, k + 1, nums);
    }
}

void permute(int * arr, int n, int * nums, int k, int * taken) {
    if (n == 1) {
        nums[k] = arr[0];
        print_number(nums, k);
        return;
    }
    int i;
    for (i = 0; i < n; i++) {
        if (taken[arr[i]]) continue;
        nums[k] = arr[i];
        taken[arr[i]] = 1;
        permute(arr, n, nums, k + 1, taken);
        taken[arr[i]] = 0;
    }
}

int max(int * arr, int len) {
    int i, max = arr[0];
    for (i = 1; i < len; i++) {
        max = max < arr[i] ? arr[i] : max;
    }
    return max;
}

void print_permutations(int * arr, int n) {
    int i;
    int nums[100] = {0};
    int * taken = (int *)calloc(max(arr, n), sizeof(int));
    for (i = 0; i < n; i++) {
        nums[0] = arr[i];
        taken[arr[i]] = 1;
        permute(arr, n, nums, 1, taken);
        taken[arr[i]] = 0;
    }
    //remove from cuurent array and permute and then add back again
}
