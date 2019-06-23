//
// Created by harsha on 2019-05-28.
//

#include "expressionEval.h"

int getPrecedence(char c) {
    switch (c) {
        case '+' : return 1;
        case '-' : return 1;
        case '*' : return 2;
        case '/' : return 2;
        case '(' : return 4;
        case 'u' : return 3;
        default: return 4;
    }
}

int isOperator(char c) {
    switch (c) {
        case '+' : return 1;
        case '-' : return 1;
        case '*' : return 1;
        case '/' : return 1;
        case '(' : return 1;
        default: return 0;
    }
}

lls * toPostfix(char * infix) {
    char ** postfix = (char **)malloc(sizeof(char **) * (strlen(infix) * 2 + 1));
    stack * operator = create_stack(strlen(infix));
    int k = 0, i = 0, last = 0, lastop = 0;
    while(infix[i]) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[k] = (char *)malloc(sizeof(char) * 10);
            int ind = 0;
            while(isalnum(infix[i])) {
                postfix[k][ind++] = infix[i++];
            }
            postfix[k++][ind] = 0;
            i--;
        }
        else {
            //push
            if (c == ')') {
                if (isEmpty(operator)) return NULL;
                while(!isEmpty(operator) && peek(operator) != '(') {
                    char op = pop(operator);
                    postfix[k] = (char *)malloc(sizeof(char) * 2);
                    postfix[k][0] = op;
                    postfix[k++][1] = 0;
                }
                pop(operator);
            } else {
                if (c == '(') {
                    push(operator, '(');
                    i++;
                    continue;
                }
                else if (c == '-' && isOperator(last)) {
                    push(operator, '~');
                    i++;
                    continue;
                }
                int precedence = getPrecedence(c);
                if (!isEmpty(operator) && getPrecedence(peek(operator)) >= precedence) {
                    while(!isEmpty(operator) && peek(operator) != '(' && getPrecedence(peek(operator)) >= precedence) {
                        char op = pop(operator);
                        postfix[k] = (char *)malloc(sizeof(char) * 2);
                        postfix[k][0] = op;
                        postfix[k++][1] = 0;
                    }
                }
                push(operator, c);
            }
            lastop = c;
        }
        last = infix[i];
        i++;
    }
    while (!isEmpty(operator)) {
        char op = pop(operator);
        postfix[k] = (char *)malloc(sizeof(char) * 2);
        postfix[k][0] = op;
        postfix[k++][1] = 0;
    }

    return init_list(postfix, k);
}

int eval(int a, int b, char op) {
    printf("%d %d %c\n", a, b, op);
    switch (op) {
        case '+' : return a + b;
        case '-' : return a - b;
        case '*' : return a * b;
        case '/' : return b != 0 ? a / b : 0;
        default: return -1;
    }
}

//TODO covert postfix from string to linked list
int evaluatePostfix(lls * postfix) {
    stack * s = create_stack(get_ll_length(postfix));
    int i = 0, num = 0, last = 48;
    lls * cur = postfix;
    lls * prev = NULL;

    while (cur != NULL) {
        if (isalnum(cur->val[0])) {
            int j = 0;
            num = 0;
            while(cur->val[j]) {
                num = num * 10 + cur->val[j++] - 48;
            }
            push(s, num);
        } else {
            if (cur->val[0] == '~') {
                if (isEmpty(s)) return 0;
                push(s, -pop(s));
            }
            else {
                int b = pop(s);
                if (isEmpty(s)) return 0;
                int a = pop(s);
                push(s, eval(a, b, cur->val[0]));
            }
        }
        cur = cur->next;
    }

    if (isEmpty(s)) return 0;
    return pop(s);
}