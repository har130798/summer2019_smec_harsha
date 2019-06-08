#include <stdio.h>
#include "structure.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_PAGES_TO_LOAD 3

void printLeaf(LeafPage * leaf) {
    int i;
    for (i = 0; i < 3;i++) {
        printf("%d %s \n", leaf->sid[i], leaf->name[i]);
    }
}

void printNonLeaf(NonLeafPage * nonLeafPage) {
    int i;
    for (i = 0; i < VALUES_PER_NLF_NODE; i++) {
        printf("%d ", nonLeafPage->value[i]);
    }
    printf("\n");
    for (i = 0; i < VALUES_PER_NLF_NODE + 1; ++i) {
        printf("%d ", nonLeafPage->childIds[i]);
    }
}

int getNodeType(void *data) {
    LeafPage * leaf = (LeafPage *)data;
    NonLeafPage * nonleaf = (NonLeafPage *)data;
    if (leaf->pageType == 1) {
        return 1;
    } else if (nonleaf->pageType == 2) {
        return 2;
    }
    else {
        printf("UNKNOWN nodetype\n");
        exit(1);
    }
}

NonLeafPage * constructNonLeafPageFromLeafs(char *filename, int numberOfLeafs) {
    FILE * f = fopen("abc.txt", "rb");
    void * buffer = malloc(PAGESIZE);
    NonLeafPage * nonLeafPage = (NonLeafPage *)malloc(sizeof(NonLeafPage));
    int i;

    for (i = 0; i < numberOfLeafs; i++) {
        fread(buffer, PAGESIZE, 1, f);
        if (getNodeType(buffer) == 1) {
            if (i == 0) {
                nonLeafPage->childIds[i] = ((LeafPage *)buffer)->sid[STUDENTS_PER_PAGE - 1];
            } else {
                nonLeafPage->value[i - 1] = ((LeafPage *)buffer)->sid[0];
            }
            nonLeafPage->childIds[i] = i;
        }
    }

    fclose(f);
    f = NULL;
    return nonLeafPage;
}

int getPage(PageInfo * pages, int id) {
    struct timeval tv;

    int i, leastUsed, usage = 0;
    for (i = 0; i < MAX_PAGES_TO_LOAD; i++) {
        if (pages[i].pageId == id) {
            gettimeofday(&tv,NULL);
            pages[i].lastTimeUsed = tv.tv_sec;
            return i;
        }
        if (i == 0) {
            leastUsed = i;
            usage = pages[i].lastTimeUsed;
        } else {
            leastUsed = pages[i].lastTimeUsed > usage ? i : leastUsed;
        }
    }

    FILE * f = fopen("abc.txt", "rb");
    void * buffer = malloc(PAGESIZE);
    fseek(f, id * PAGESIZE, SEEK_SET);
    fread(buffer, PAGESIZE, 1, f);
    fclose(f);
    f = NULL;

    memcpy(pages[i].pageBuffer, buffer, PAGESIZE);
    gettimeofday(&tv,NULL);
    pages[i].lastTimeUsed = tv.tv_sec;
    return leastUsed;
}

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

int searchNonLeaf(int val, NonLeafPage * page) {
//    int strt = 0;
//    int end = VALUES_PER_NLF_NODE - 1;
//
//    if (val < page->childIds[strt]) {
//
//    }
//
//    while (strt < end) {
//        int mid = () / 2;
//
//    }
}

void run_query(PageInfo * pages, int val) {
    //load nlp
    int pageIndex = getPage(pages, 4);
    NonLeafPage * page = (NonLeafPage *)pages[pageIndex].pageBuffer;




}

int main() {
    int numberOfLeafs = 4;
    LeafPage page[numberOfLeafs];
    char filename[10] = "abc.txt";

    int studentStartId = 10;
    int i;
    for (i = 0; i < 4;i++) {
        page[i].pageType = 1;
        int j;
        for (j = 0; j < STUDENTS_PER_PAGE; j++) {
            page[i].sid[j] = studentStartId;
            studentStartId += 10;
        }
    }

    strcpy(page[0].name[0], "aman");
    strcpy(page[0].name[1], "anu");
    strcpy(page[0].name[2], "bala");
    strcpy(page[1].name[0], "bapu");
    strcpy(page[1].name[1], "don");
    strcpy(page[1].name[2], "eega");
    strcpy(page[2].name[0], "fana");
    strcpy(page[2].name[1], "guna");
    strcpy(page[2].name[2], "hema");
    strcpy(page[3].name[0], "isac");
    strcpy(page[3].name[1], "jai");
    strcpy(page[3].name[2], "sana");

    FILE * f = fopen(filename, "wb");

    for (i = 0; i < numberOfLeafs; i++) {
        fwrite(&page[i], PAGESIZE, 1, f);
    }

    fclose(f);
    f = NULL;

    PageInfo * pages = (PageInfo *)malloc(sizeof(PageInfo) * MAX_PAGES_TO_LOAD);

    for (i = 0; i < MAX_PAGES_TO_LOAD; i++) {
        pages[i].pageId = -1;
        pages[i].lastTimeUsed = 0;
    }


    printNonLeaf(constructNonLeafPageFromLeafs(filename, numberOfLeafs));
    return 0;
}