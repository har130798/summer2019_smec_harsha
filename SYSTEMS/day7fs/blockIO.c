//
// Created by harsha on 2019-05-31.
//

#include "blockIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "futils.h"

static unsigned int BlockSize;
static char Diskname[30];

void * allocateBlockFromMemory() {
    void * block = malloc(sizeof(void) * BlockSize);
    if (block == NULL) {
        printf("Block allocation failed!");
        exit(1);
    }

    return block;
}

unsigned int init(char *diskName, unsigned int blockSize) {
    strcpy(Diskname, diskName);
    BlockSize = blockSize;
    unsigned int TotalBlocks = getFilesize(diskName) / blockSize;

    return TotalBlocks;
}

void write_block(void *block, unsigned int pos) {
    FILE * disk = open_file(Diskname, "rb+");
    fseek(disk, pos * BlockSize, SEEK_SET);

    fwrite(block, sizeof(void), BlockSize, disk);

    close_file(disk);
}

void * read_block(unsigned int pos) {
    FILE *disk = open_file(Diskname, "rb+");
    fseek(disk, pos * BlockSize, SEEK_SET);

    void *block = allocateBlockFromMemory();
    if (fread(block, BlockSize, 1, disk) == 0) {
        close_file(disk);
        printf("Unable to read disk! May have reached EOF\n");
        return NULL;
    }

    close_file(disk);
    return block;
}
