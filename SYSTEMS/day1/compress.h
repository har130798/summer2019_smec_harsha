//
// Created by harsha on 2019-05-25.
//

#ifndef DAY1_COMPRESS_H
#define DAY1_COMPRESS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int get_number_of_digits(int num) {
    int c = 0;
    do {
        c++;
        num /= 10;
    } while (num > 0);

    return c;
}

char * numToChar(int num) { // try power
    int i, n = num;
    int size = get_number_of_digits(num);
    char * s = (char *)malloc(sizeof(char) * (size + 1));
    int index = size - 1;
    do {
        s[index] = num % 10 + 48;
        num /= 10;
    } while(num > 0);
    s[size] = 0;
    return s;
}

void compress(char * input){
    if (input == NULL || input[0] == 0) {
        return;
    }
    int i, j, count = 1;
    char cur = input[0];
    int cur_index = 1;
    for (i = 1; input[i]; i++) {
        if (cur == input[i]) {
            count++;
        } else {
            if (count > 1) {
                //convert number and append
                char * strcount = numToChar(count);
                for (j = 0; strcount[j]; j++) {
                    input[cur_index++] = strcount[j];
                }
                //power method

                // int digits = get_number_of_digits(count);
                // if (digits == 1) {
                //     input[cur_index++] = count + 48;
                // } else {
                //     int exp = digits - 1;
                //     while(exp > -1) {
                //         int digit = count / pow(10, exp);
                //         input[cur_index++] = digit + 48;
                //         count %= (int)pow(10, exp);
                //         exp--;
                //     }
                // }
            }
            cur = input[i];
            input[cur_index++] = cur;
            count = 1;
        }
    }
    //append number
    if (count > 1) {
        char * strcount = numToChar(count);
        for (j = 0; strcount[j]; j++) {
            input[cur_index++] = strcount[j];
        }
    }
    input[cur_index] = 0;
}
#endif //DAY1_COMPRESS_H
