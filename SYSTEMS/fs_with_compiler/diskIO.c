//
// Created by harsha on 2019-05-31.
//

#include "diskIO.h"

//
// Created by harsha on 2019-05-30.
//

#include "structure.h"
#include <stdio.h>
#include "utils.h"

static unsigned int BlockSize;
static unsigned int TotalBlocks;
static char Diskname[30];

void * allocateBlockFromMemory() {
    void * block = malloc(sizeof(void) * BLOCK_SIZE);
    if (block == NULL) {
        printf("Block allocation failed!");
        exit(1);
    }

    return block;
}

unsigned int initDisk(char * diskName, unsigned int blockSize) {
    strcpy(Diskname, diskName);
    BlockSize = blockSize;
    TotalBlocks = getFilesize(diskName) / blockSize;
    return TotalBlocks;
}

void write_block(void *block, unsigned int pos) {
    FILE * disk = open_file(filename, "rb+");
    fseek(disk, pos * BLOCK_SIZE, SEEK_SET);

    fwrite(block, sizeof(void), BLOCK_SIZE, disk);

    close_file(disk);
}

void * read_block(unsigned int pos) {
    FILE * disk = open_file(filename, "rb+");
    fseek(disk, pos * BLOCK_SIZE, SEEK_SET);

    void * block = allocateBlockFromMemory();
    if (fread(block, BLOCK_SIZE, 1, disk) == 0) {
        close_file(disk);
        printf("Unable to read disk! May have reached EOF\n");
        return NULL;
    }

    close_file(disk);
    return block;
}
