//
// Created by harsha on 2019-05-26.
//

#include "mergesort_dll.h"

dll * create_dll_node(int val) {
    dll * newnode = (dll *)malloc(sizeof(dll));
    newnode->val = val;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

void print_dll(dll * head) {
    dll * temp = head;
    while(temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

dll * get_middle_node_dll(dll * head) {
    dll * slow = head;
    dll * fast = head;

    while(fast != NULL) {
        slow = slow->next;
        fast = fast->next != NULL ? fast->next->next : NULL;
    }
    return slow;
}

dll * make_dll(int * arr, int len) {
    int i;
    dll * head = create_dll_node(arr[0]);
    dll * temp = head;
    for(i = 1; i < len; i++) {
        temp->next = create_dll_node(arr[i]);
        temp->next->prev = temp;
        temp = temp->next;
    }
    return head;
}

int get_dll_length(dll * head) {
    int count = 0;
    dll * temp = head;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

dll * get_tail_dll(dll * head) {
    if (head == NULL)
        return head;
    dll * tail = head;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    return tail;
}

dll * split_by_middle_element(dll * head) {
    if (head == NULL) {
        return NULL;
    }

    dll * mid = get_middle_node_dll(head);
    if (mid == head) {
        return mid;
    }

    dll * mid_prev = mid->prev;
    mid_prev->next = NULL;
    mid->prev = NULL;
    return mid;
}

dll * mergesort_dll(dll * head) {
    if(head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        return head;
    }

    dll * middle = split_by_middle_element(head);

    dll * lefthalf = mergesort_dll(head);
    dll * righthalf = mergesort_dll(middle);
    return merge(lefthalf, righthalf);
}

dll * merge(dll * l1, dll * l2) {
    dll * t1, * t2;
    dll * head;
    if (l1->val >= l2->val) {
        head = l2;
        t1 = l2->next;
        t2 = l1;
    } else {
        head = l1;
        t1 = l1->next;
        t2 = l2;
    }

    while(t1 != NULL && t2 != NULL) {
        if (t2->val >= t1->val) {
            t1 = t1->next;
        } else {
            dll * t2next = t2->next;
            t1->prev->next = t2;
            t2->prev = t1->prev;
            t1->prev = t2;
            t2->next = t1;
            t2 = t2next;
        }
    }

    if (t1 == NULL && t2 != NULL) {
        dll * t1tail = get_tail_dll(head);
        t1tail->next = t2;
        t2->prev = t1tail;
    }

    return head;
}

