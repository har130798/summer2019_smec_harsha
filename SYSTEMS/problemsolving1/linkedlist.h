//
// Created by harsha on 2019-05-25.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<stdio.h>
#include<stdlib.h>

typedef struct ll {
    int val;
    struct ll * next;
}ll;

ll * create_node(int val) {
    ll * node = (ll *)malloc(sizeof(ll));
    node->val = val;
    node->next = NULL;
    return node;
}

void delete_list(ll * node) {
    if (node == NULL) return;
    ll * t = node->next;
    free(node);
    node = NULL;
    delete_list(t);
}

void print_list(ll * node) {
    if (node == NULL) {
        printf("\n");
        return;
    }
    ll * t = node->next;
    printf("%d ", node->val);
    print_list(t);
}

ll * init_list(int * arr, int len) {
    if (arr == NULL || len <= 0) {
        return NULL;
    }
    int i;
    ll * root, * temp;
    root = create_node(arr[0]);
    temp = root;
    for (i = 1; i < len; i++) {
        temp->next = create_node(arr[i]);
        temp = temp->next;
    }
    return root;
}

int get_ll_length(ll * node) {
    int c = 0;
    ll * temp = node;
    while(temp != NULL) {
        c++;
        temp = temp->next;
    }
    return c;
}

ll * reverse_list(ll * head) {
    ll * prev = NULL;
    ll * cur = head;
    while(cur != NULL) {
        ll * temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    head = prev;
    return head;
}

#endif
