//
// Created by harsha on 2019-05-30.
//

#ifndef FSYSTEM_STRUCTURE_H
#define FSYSTEM_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_KEY 0x444E524D
#define MAX_BLOCKS 6400
#define BLOCK_SIZE 16384
#define START_BLOCK 3

#define MAX_TABLE_SIZE 32
#define START_POS 49152 // 4th block
#define TOTAL_SPACE 104808448


typedef struct TableEntry {
    char name[20];
    unsigned int start;
    unsigned int noOfBlocks;
    unsigned int fileLength;
}TableEntry;

typedef struct Metadata {
    unsigned int startKey;
    TableEntry files[MAX_TABLE_SIZE];
    unsigned int tableSize;
    char freeBlocks[MAX_BLOCKS];
    unsigned int freeSpace;
}Metadata;

int addEntryToMetadata(Metadata *metadata, char *name, unsigned int start,
        unsigned noOfBlocks, unsigned int fileLength);

#endif //FSYSTEM_STRUCTURE_H
