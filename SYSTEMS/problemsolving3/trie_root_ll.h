//
// Created by harsha on 2019-05-31.
//

#ifndef DAY5_TRIE_ROOT_LL_H
#define DAY5_TRIE_ROOT_LL_H

#include "lls.h"

typedef struct trienode {
    char val;
    char * next;
    lls * llhead;
}trienode;

#endif //DAY5_TRIE_ROOT_LL_H
