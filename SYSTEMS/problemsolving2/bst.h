//
// Created by harsha on 2019-05-26.
//

#ifndef BST_H
#define BST_H

#include<stdio.h>
#include<stdlib.h>

typedef struct bst_node {
    int val;
    struct bst_node * left;
    struct bst_node * right;
}bst_node;

bst_node * create_bst_node(int val) {
    bst_node * node = (bst_node *)malloc(sizeof(bst_node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert_bst_node(bst_node * node, int val) {
    if (node == NULL) {
        node = create_bst_node(val);
        return;
    }

    if (val >= node->val) { // traverse right
        if (node->right == NULL) {
            bst_node * new_node = create_bst_node(val);
            node->right = new_node;
        } else {
            insert_bst_node(node->right, val);
        }
    } else {//traverse left
        if (node->left == NULL) {
            bst_node * newnode = create_bst_node(val);
            node->left = newnode;
        } else {
            insert_bst_node(node->left, val);
        }
    }
}

void print_bst(bst_node * node) {//preorder
    if (node == NULL) {
        return;
    }
    print_bst(node->left);
    printf("%d ", node->val);
    print_bst(node->right);
}

bst_node * make_bst(int * arr, int len) {
    int i;
    bst_node * root = create_bst_node(arr[0]);
    for (i = 1; i < len; i++) {
        insert_bst_node(root, arr[i]);
        // print_bst(root);
    }
    return root;
}

#endif //DAY2_BST_H
