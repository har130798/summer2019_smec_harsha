//
// Created by harsha on 2019-05-25.
//

#ifndef DAY1_REVERSEEVERYKNODES_H
#define DAY1_REVERSEEVERYKNODES_H

#include"linkedlist.h"

void reverse_sub_list(ll * start, ll * end) {
    ll * prev = start;
    ll * cur = start->next;
    while(prev != end) {
        ll * t = cur->next;
        cur->next = prev;
        prev = cur;
        cur = t;
    }
}

ll * reverseEveryKNodes(ll * head, int k) {
    if (head == NULL) return head;

    if (k < 1) {
        return head;
    }
    int lim = get_ll_length(head) / k;

    int first = 1;
    ll * begin = head;
    ll * end, * prev_end;

    while (lim--)
    {
        end = begin;
        int trav = k - 1;
        while(trav--) {
            end = end->next;
        }
        ll * next_begin = end->next;
        reverse_sub_list(begin, end);
        if (first) {
            head = end;
            first = 0;
            prev_end = begin;
        } else {
            prev_end->next = end;
            prev_end = begin;
        }
        begin->next = next_begin;
        begin = next_begin;
        // print_list(head);
    }
    return head;
}

#endif //DAY1_REVERSEEVERYKNODES_H
