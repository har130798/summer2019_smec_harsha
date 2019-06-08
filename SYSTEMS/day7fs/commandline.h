//
// Created by harsha on 2019-05-31.
//

#ifndef DAY7FS_COMMANDLINE_H
#define DAY7FS_COMMANDLINE_H

typedef struct Metadata {
    unsigned int magic;
    unsigned int blockSize;
    unsigned int totalBlocks;
    unsigned int emptyBlocks;
    char freeBlocks[1];
}Metadata;

typedef struct TableEntry {
    char name[20];
    unsigned int blockCount;
    unsigned int fileSize;
    unsigned int startingBlock;
}TableEntry;

typedef struct FileTable {
    unsigned int filesCount;
    TableEntry files[1];
}FileTable;

void take_command();

#endif //DAY7FS_COMMANDLINE_H
