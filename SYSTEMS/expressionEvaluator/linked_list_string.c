//
// Created by harsha on 2019-05-28.
//

#include "linked_list_string.h"


lls * create_node(char * val) {
    lls * node = (lls *)malloc(sizeof(lls));
    node->val = (char *)malloc(sizeof(strlen(val) + 1));
    strcpy(node->val, val);
    node->next = NULL;
    return node;
}

void delete_list(lls * node) {
    if (node == NULL) return;
    lls * t = node->next;
    free(node);
    node = NULL;
    delete_list(t);
}

void print_list(lls * node) {
    if (node == NULL) {
        printf("\n");
        return;
    }
    lls * t = node->next;
    printf("%s ", node->val);
    print_list(t);
}

lls * init_list(char ** arr, int len) {
    if (arr == NULL || len <= 0) {
        return NULL;
    }
    int i;
    lls * root, * temp;
    root = create_node(arr[0]);
    temp = root;
    for (i = 1; i < len; i++) {
        temp->next = create_node(arr[i]);
        temp = temp->next;
    }
    return root;
}

int get_ll_length(lls * node) {
    int c = 0;
    lls * temp = node;
    while(temp != NULL) {
        c++;
        temp = temp->next;
    }
    return c;
}