#include <stdio.h>
#include "commandline.h"

void runapp() {
    take_command();
}

void test() {
    Metadata a;
    printf("%d\n", sizeof(Metadata));
    printf("%d\n", sizeof(TableEntry));
    printf("%d\n", sizeof(FileTable));
}


int main() {
//    runapp();
    test();
    return 0;
}