//
// Created by harsha on 2019-05-26.
//

#ifndef TRIE_H
#define TRIE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct trie {
    char val;
    struct trie * next[256];
}trie;

trie * trienode(char val) {
    trie * node = (trie *)malloc(sizeof(trie));
    node->val = val;
    int i;
    for(i = 0; i < 256; i++) {
        node->next[i] = NULL;
    }
    return node;
}

void insert_word(trie * node, char * s, int index, int len) {
    if (len == index) {
        //only for q1 set 1
        // trie * nextnode = trienode(0);
        // node->next[0] = nextnode;
        return;
    }

    if (node->next[s[index]] != NULL) {
        return insert_word(node->next[s[index]], s, index + 1, len);
    }

    trie * nextnode = trienode(s[index]);
    node->next[s[index]] = nextnode;
    insert_word(nextnode, s, index + 1, len);
}

trie * make_trie(char ** strs, int length) {
    trie * root = trienode(0);
    int i;
    for(i = 0; i < length; i++) {
        insert_word(root, strs[i], 0, strlen(strs[i]));
    }
    return root;
}

int hasChild(trie * node) {
    int i;
    for (i = 0; i < 256; i++) {
        if (node->next[i] != NULL) return 1;
    }
    return 0;
}

#endif //TRIE_H
