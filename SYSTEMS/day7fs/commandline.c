//
// Created by harsha on 2019-05-31.
//

#include "commandline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockIO.h"

#define MAGIC_NUMBER 0x444E524D
static unsigned int BlockSize;
static unsigned int totalBlocks;

void writeMetadata(Metadata * metadata, FileTable * fileTable) {

}

void mount(char * filename, unsigned int blocksize) {
    totalBlocks = init(filename, blocksize);
    void * firstBlock = read_block(0);
    int magicCheck;

    memcpy(&magicCheck, firstBlock, sizeof(int));
    if (magicCheck != MAGIC_NUMBER) {
        //TODO FORMAT
        return;
    }

    unsigned int totalMetadataSize = 16 + totalBlocks;

    Metadata * metadata = (Metadata *)malloc(totalMetadataSize);

    unsigned int blockReadsRequired;

    if (totalMetadataSize / BlockSize == 0) {
        blockReadsRequired = 1;
    } else {
        if (totalMetadataSize % BlockSize == 0) {
            blockReadsRequired = totalMetadataSize / BlockSize;
        } else {
            blockReadsRequired = totalMetadataSize / BlockSize + 1;
        }
    }

    void * buffer = malloc(BlockSize * blockReadsRequired);


}

void take_command() {
    while (1) {
        char s[32];
        scanf(" %s", s);
        if (strcasecmp(s, "init") == 0) {

            unsigned int blocksize;
            char diskName[30];

            scanf(" %s", diskName);
//            BlockSize = ;

        } else if (strcasecmp(s, "copytodisk") == 0) {

            char arg1[16], arg2[16];
            scanf(" %s %s", arg1, arg2);
//            copyToDisk(arg1, arg2, metadata);

        } else if (strcasecmp(s, "list") == 0) {

//            listFiles(metadata);

        } else if (strcasecmp(s, "copyfromdisk") == 0) {

            char arg1[16], arg2[16];
            scanf(" %s %s", arg1, arg2);
//            copyFromDisk(arg1, arg2, metadata);

        } else if(strcasecmp(s, "exit") == 0) {

            break;

        } else if (strcasecmp(s, "format") == 0) {

//            formatDisk();
//            free(metadata);
//            metadata = createMetadataTable();

        } else if (strcasecmp(s, "delete") == 0) {

//            char arg[32];
//            scanf(" %s", arg);
//            deleteFileFromDisk(arg, metadata);

        } else if (strcasecmp(s, "debug") == 0) {

//            debugPrint(metadata);

        } else {

            printf("Command not found\n");

        }
    }
}
