#include "controller.h"

//call init
//call run
//  |-- take command
//  |-- process it
//  |-- call appropriate lib
//  |-- repeat
//call kill

int main() {

    cell *** state = init_app();
    run_app(state);
    kill_app(state);
//    cell * t = create_cell(10, NULL);
//    parse_set_argument("a1=b3*b6", t);
//    printf("%s%d\n", t->expression == NULL ? "NULL " : t->expression, t->val);
//    parse_set_argument("a1=10", t);
//    printf("%s%d\n", t->expression == NULL ? "NULL " : t->expression, t->val);
    return 0;
}