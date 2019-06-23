//
// Created by harsha on 2019-05-28.
//

#ifndef DAY4_EXPRESSIONEVAL_H
#define DAY4_EXPRESSIONEVAL_H

#include "my_stack.h"
#include "linked_list_string.h"
#include <string.h>
#include <ctype.h>

lls * toPostfix(char * infix);

int getPrecedence(char c);

int evaluatePostfix(lls * postfix);

#endif //DAY4_EXPRESSIONEVAL_H
