//
// Created by harsha on 2019-05-30.
//

#ifndef FSYSTEM_DISK_H
#define FSYSTEM_DISK_H

#define filename "../disk.hdd"

void write_block(void *block, unsigned int pos);
void * read_block(unsigned int pos);
void * allocateBlockFromMemory();
void freeBlockFromMemory(void * ptr);
unsigned int initDisk(char * diskName, unsigned int blockSize);

#endif //FSYSTEM_DISK_H
