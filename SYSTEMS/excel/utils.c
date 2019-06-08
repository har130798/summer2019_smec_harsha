//
// Created by harsha on 2019-05-27.
//

#include "utils.h"


void close_file(FILE * f) {
    fclose(f);
    f = NULL;
}

FILE * open_file(char * name, char * mode) {
    FILE * f = fopen(name, mode);
    return f;
}

int compareStringsCaseInsensitive(char * a, char * b) {
    return a!= NULL && b != NULL && strcasecmp(a, b) == 0 ? 1 : 0;
}

char *** create_grid(int m, int n) {
    int init_val = 0, i, j;
    int ** mat = (int **)malloc(sizeof(int *) * m);
    for (i = 0; i < m; i++) {
        mat[i] = (int *)malloc(sizeof(int) * n);
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j] = init_val;
        }
    }
    return mat;
}

char * create_string(int len) {
    return (char *)malloc(sizeof(char) * (len + 1));
}

char * trim(char * input) {
    char * newstring = create_string(strlen(input));
    int start = 0;
    while(input[start] == ' ' || input[start] == '>') start++;
    int end = strlen(input) - 1;
    while (input[end] == ' ') end--;
    int i, k = 0;
    for (i = start; i < end + 1; i++) {
        newstring[k++] = input[i];
    }
    newstring[k] = 0;
    return newstring;
}

int get_number_from_start_till_end(char * s, int start) {
    int n = 0,i = 0;
    for (i = start; s[i]; i++) {
        n = n * 10 + s[i] - 48;
    }
    return n;
}

void print_grid(int ** mat, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

char * reverse_string(char * s) {
    int i, len = strlen(s);
    char * newstr = create_string(len);
//    printf("%s\n", s);
    for(i = 0; s[i]; i++) {
        newstr[len - 1 - i] = s[i];
    }
    newstr[len] = 0;
    return newstr;
}

char * toString(int n) {
    char * num = create_string(10);
    int k = 0;
    do {
        num[k++] = n % 10 + 48;
        n /= 10;
    }while (n);
    num[k] = 0;
    return reverse_string(num);
}

int hasAlpha(char * s) {
    int i = 0;
    while(s[i]) {
        if (isalpha(s[i]))
            return 1;
        i++;
    }
    return 0;
}