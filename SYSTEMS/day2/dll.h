//
// Created by harsha on 2019-05-26.
//

#ifndef DLL_H
#define DLL_H
//
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct dll {
//    int val;
//    struct dll * next;
//    struct dll * prev;
//}dll;
//
//dll * create_dll_node(int val) {
//    dll * newnode = (dll *)malloc(sizeof(dll));
//    newnode->val = val;
//    newnode->next = NULL;
//    newnode->prev = NULL;
//    return newnode;
//}
//
//void print_dll(dll * head) {
//    dll * temp = head;
//    while(temp != NULL) {
//        printf("%d ", temp->val);
//        temp = temp->next;
//    }
//    printf("\n");
//}
//
//dll * get_middle_node_dll(dll * head) {
//    dll * slow = head;
//    dll * fast = head;
//
//    while(fast != NULL) {
//        slow = slow->next;
//        fast = fast->next != NULL ? fast->next->next : NULL;
//    }
//    return slow;
//}
//
//dll * make_dll(int * arr, int len) {
//    int i;
//    dll * head = create_dll_node(arr[0]);
//    dll * temp = head;
//    for(i = 1; i < len; i++) {
//        temp->next = create_dll_node(arr[i]);
//        temp->next->prev = temp;
//        temp = temp->next;
//    }
//    return head;
//}
//
//int get_dll_length(dll * head) {
//    int count = 0;
//    dll * temp = head;
//    while(temp != NULL) {
//        count++;
//        temp = temp->next;
//    }
//    return count;
//}
//
//dll * get_tail_dll(dll * head) {
//    if (head == NULL)
//        return head;
//    dll * tail = head;
//    while(tail->next != NULL) {
//        tail = tail->next;
//    }
//    return tail;
//}
//
//dll * split_by_middle_element(dll * head) {
//    if (head == NULL) {
//        return NULL;
//    }
//
//    dll * mid = get_middle_node_dll(head);
//    if (mid == head) {
//        return mid;
//    }
//
//    dll * mid_prev = mid->prev;
//    mid_prev->next = NULL;
//    mid->prev = NULL;
//    return mid;
//}
#endif
