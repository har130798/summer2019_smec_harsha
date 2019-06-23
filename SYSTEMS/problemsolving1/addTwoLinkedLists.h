//
// Created by harsha on 2019-05-25.
//

#ifndef DAY1_ADDTWOLINKEDLISTS_H
#define DAY1_ADDTWOLINKEDLISTS_H

//
// Created by harsha on 2019-05-25.
//
#ifndef ADDLINKEDLISTS_C
#define ADDLINKEDLISTS_C
#include "linkedlist.h"

ll * addTwoLinkedLists(ll * a, ll * b) {
    a = reverse_list(a);
    b = reverse_list(b);
    int carry = 0, first = 1;
    ll * a_cur = a;
    ll * b_cur = b;
    ll * new_head, * new_prev;
    while(a_cur != NULL && b_cur != NULL) {
        int sum = a_cur->val + b_cur->val + carry;
        ll * newnode = create_node(sum % 10);
        carry = sum / 10;
        if (first) {
            first = 0;
            new_head = newnode;
            new_prev = newnode;
        } else {
            new_prev->next = newnode;
            new_prev = newnode;
        }
        a_cur = a_cur->next;
        b_cur = b_cur->next;
    }

    if (a_cur != NULL) {
        while(a_cur != NULL) {
            int sum = a_cur->val + carry;
            ll * newnode = create_node(sum % 10);
            carry = sum / 10;
            new_prev->next = newnode;
            new_prev = newnode;
            b_cur = b_cur->next;
        }

    } else if (b_cur != NULL) {
        while(b_cur != NULL) {
            int sum = b_cur->val + carry;
            ll * newnode = create_node(sum % 10);
            carry = sum / 10;
            new_prev->next = newnode;
            new_prev = newnode;
            b_cur = b_cur->next;
        }
    }

    if (carry != 0) {
        while(carry != 0) {
            new_prev->next = create_node(carry % 10);
            carry /= 10;
            new_prev = new_prev->next;
        }
    }
    new_head = reverse_list(new_head);
    a = reverse_list(a);
    b = reverse_list(b);
    print_list(a);
    print_list(b);
    return new_head;
}

#endif

#endif //DAY1_ADDTWOLINKEDLISTS_H
