//
// Created by harsha on 2019-05-27.
//

#include "SET.h"

void set(cell *** sheet, char * arg) {

    //Add error checking here
    int col_number = arg[0] > 96 ? arg[0] - 97 : arg[0] - 65;
    int row_number = arg[1] - 48;

    if (sheet == NULL) {
        return;
    }

    parse_set_argument(arg, sheet[row_number - 1][col_number]);
}

void parse_set_argument(char * arg, cell * toCopyInto) {
    //call invalid expression EVAL here
    int i = 3;
    int exp = 1;
    if (arg[i] == '"' || arg[i] == '\'') {
        exp = 2;
    } else if(isAlphaSubString(arg, 3, strlen(arg)) || isNumberSubString(arg, 3, strlen(arg))) {
        exp = 0;
    }

    if (exp == 1) {
        char * s = create_string(strlen(arg) - 3);
        int k = 0;
        for (i = 3; arg[i]; i++) {
            s[k++] = arg[i];
        }
        s[k] = 0;
        if (toCopyInto->expression != NULL) {
            free(toCopyInto->expression);
            toCopyInto->expression = NULL;
        }
        toCopyInto->expression = s;
    } else if (exp == 0){
        toCopyInto->val = create_string(strlen(arg));
        copySubString(toCopyInto->val, arg, 3, strlen(arg));
        if (toCopyInto->expression != NULL) {
            free(toCopyInto->expression);
            toCopyInto->expression = NULL;
        }
    } else {
        toCopyInto->val = create_string(strlen(arg));
        copySubString(toCopyInto->val, arg, 4, strlen(arg) - 1);
        if (toCopyInto->expression != NULL) {
            free(toCopyInto->expression);
            toCopyInto->expression = NULL;
        }
    }
}

int isNumberSubString(char * s, int start, int end) {
    int i = start;
    while(i < end) {
        if (!isnumber(s[i]))
            return 0;
        i++;
    }
    return 1;
}

int isAlphaSubString(char * s, int start, int end) {
    int i = start;
    while(i < end) {
        if (!isalpha(s[i]))
            return 0;
        i++;
    }
    return 1;
}

int copySubString(char * dest, const char * src, int start, int end) {
    int i = start;
    while(i < end) {
        dest[i - start] = src[i];
        i++;
    }
    dest[end] = 0;
    return 1;
}