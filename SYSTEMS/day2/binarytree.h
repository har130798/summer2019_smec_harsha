//
// Created by harsha on 2019-05-26.
//

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include<stdio.h>
#include<stdlib.h>

typedef struct treenode {
    int val;
    struct treenode * left;
    struct treenode * right;
    struct treenode * nextRight;
}treenode;

treenode * create_tree_node(int val) {
    treenode * node = (treenode *)malloc(sizeof(treenode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int isLeaf(treenode * node) {
    if (node == NULL) return 0;
    return node->left == NULL && node->right == NULL ? 1 : 0;
}

void print_tree(treenode * node) {//preorder
    if (node == NULL) {
        return;
    }
    print_tree(node->left);
    printf("%d ", node->val);
    print_tree(node->right);
}

#endif
