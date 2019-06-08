//
// Created by harsha on 2019-06-02.
//

#ifndef BPLUSTREES_STRUCTURE_H
#define BPLUSTREES_STRUCTURE_H

#define PAGESIZE 32
#define STUDENTS_PER_PAGE 3
#define VALUES_PER_NLF_NODE (PAGESIZE / (sizeof(int) * 2) - 1)

typedef struct LeafPage {
    int sid[3];
    //packing problem
    char pageType;
    char unused[4];
    char name[3][5];
}LeafPage;

typedef struct NonLeafPage {
    char pageType;
    char unused[3];
    int childIds[VALUES_PER_NLF_NODE + 1];
    int value[VALUES_PER_NLF_NODE];
}NonLeafPage;

typedef struct PageInfo {
    char pageBuffer[PAGESIZE];
    int bufferUsed;
    int lastTimeUsed;
    int pageId;
}PageInfo;

#endif
