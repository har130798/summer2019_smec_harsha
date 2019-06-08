//
// Created by harsha on 2019-05-25.
//

#ifndef DAY1_LOOPINLINKEDLIST_H
#define DAY1_LOOPINLINKEDLIST_H

#include "linkedlist.h"

int getLoopFirstNode(ll * head) {
    if (head == NULL) {
        return 0;
    }
    ll * slow = head;
    ll * fast = head->next;

    while(slow != NULL && fast != NULL) {
        if(slow == fast) {
            return 1;
        }
        slow = slow->next;
        fast = fast->next != NULL ? fast->next->next : NULL;
    }

    if (slow == fast) {
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return 0;
}

#endif //DAY1_LOOPINLINKEDLIST_H
