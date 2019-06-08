//
// Created by harsha on 2019-05-30.
//

#include "structure.h"

//TableEntry * createTableEntry(char * name, unsigned int start, unsigned int size) {
//    TableEntry * entry = (TableEntry *)malloc(sizeof(TableEntry));
//    int lenName = strlen(name);
//    entry->name = (char *)malloc(sizeof(char) * (lenName + 1));
//    strcpy(entry->name, name);
//    entry->start = start;
//    entry->size = size;
//    return entry;
//}

int addEntryToMetadata(Metadata *metadata, char *name, unsigned int start,
        unsigned noOfBlocks, unsigned int fileLength) {
    if (MAX_TABLE_SIZE == metadata->tableSize) {
        return 0;
    }

    int fileIndex = metadata->tableSize;

    strcpy(metadata->files[fileIndex].name, name);
    metadata->files[fileIndex].start = start;
    metadata->files[fileIndex].noOfBlocks = noOfBlocks;
    metadata->files[fileIndex].fileLength = fileLength;

    metadata->tableSize++;

    return 1;
}

