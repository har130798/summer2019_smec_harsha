//
// Created by harsha on 2019-05-31.
//

#ifndef DAY7FS_BLOCKIO_H
#define DAY7FS_BLOCKIO_H

void write_block(void *block, unsigned int pos);
void * read_block(unsigned int pos);
void * allocateBlockFromMemory();
void freeBlockFromMemory(void * ptr);
unsigned int init(char *diskName, unsigned int blockSize);

#endif //DAY7FS_BLOCKIO_H
