#include "file_helpers.h"
#include <string.h>

typedef struct test {
    int data;
    char a[10];
}test;

void test_io() {
    test * a = (test *)malloc(sizeof(test));
    a->data = 100000000;
    strcpy(a->a, "abcdef");

    test * b = (test *)malloc(sizeof(test));

    void * z1 = malloc(sizeof(void) * sizeof(test));
    memcpy(z1, a, sizeof(test));

    void * z = malloc(sizeof(void) * sizeof(test));

    int i;

    for (i = 0; i < sizeof(test); i++) {
        memcpy(&z[i], &z1[i], 1);
    }


    memcpy(b, z, sizeof(test));
    return;
}

int main() {
    printf("Hello, World!\n");
    test_io();
    return 0;
}