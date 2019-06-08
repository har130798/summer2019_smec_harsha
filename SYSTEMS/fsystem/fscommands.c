//
// Created by harsha on 2019-05-30.
//

#include "fscommands.h"
#include "disk.h"
#include "utils.h"

Metadata * createMetadataTable() {
    Metadata * metadata = (Metadata *)malloc(sizeof(Metadata));

    metadata->startKey = START_KEY;
    metadata->tableSize = 0;
    metadata->freeSpace = TOTAL_SPACE;

    int i;
    for(i = 0; i < MAX_BLOCKS; i++) {
        metadata->freeBlocks[i] = 1;
    }

    return metadata;
}

Metadata * initMetadata() {
    int i, blocksRequired = sizeof(Metadata) / BLOCK_SIZE;
    if (sizeof(Metadata) % BLOCK_SIZE != 0) blocksRequired += 1;

    Metadata * metadata = (Metadata *)malloc(sizeof(Metadata));
    void * buffer = malloc(sizeof(void) * BLOCK_SIZE * blocksRequired);

    for (i = 0; i < blocksRequired; i++) {
        void * out = read_block(i);
        memcpy(&buffer[i * BLOCK_SIZE], out, BLOCK_SIZE);
    }

    memcpy(metadata, buffer, sizeof(Metadata));

    if (metadata->startKey != START_KEY) {
        printf("Invalid disk format!\n");
        printf("Do you want to format?(y/n)\n");
        char c;
        scanf(" %c", &c);
        if (c == 'y' || c == 'Y') {
            formatDisk();
        } else {
            exit(0);
        }
        return createMetadataTable();

    }

    printf("Loaded Disk\n");
    return metadata;
}


//TODO Modify this
void listFiles (Metadata * metadata) {
//    FILE * disk = open_file(filename, "rb+");
//    int max = metadata->tableSize;
//
//    fseek(disk, sizeof(unsigned int), SEEK_SET);
//    TableEntry * entry;
//
//    int pos = 0;
//    while (max--) {
//        entry = (TableEntry *)read_block(pos++);
//        if (entry == NULL) {
//            printf("Unable to list files :( \n");
//            close_file(disk);
//            return;
//        }
//        printf("%s\n", entry->name);
//    }
//    close_file(disk);

    if (metadata->tableSize == 0) {
        printf("No files exist!\n");
    }

    int i;
    for (i = 0; i < metadata->tableSize; i++) {
        printf("%s\n", metadata->files[i].name);
    }
}

//void printMetadata

void writeMetadataToFile(Metadata * toWrite) {
    int i, blocksRequired = sizeof(Metadata) / BLOCK_SIZE;
    if (sizeof(Metadata) % BLOCK_SIZE != 0) blocksRequired += 1;

    void * buffer = malloc(sizeof(Metadata));
    memcpy(buffer, toWrite, sizeof(Metadata));

    for (i = 0; i < blocksRequired; i++) {
        write_block(&buffer[i* BLOCK_SIZE], i);
    }
}

unsigned int getFileStart(Metadata *metadata, int requiredBlocks) {
    int i, count = requiredBlocks;
    unsigned int startBlock = 0;

    if (metadata->freeSpace <= requiredBlocks) return 0;

    for (i = START_BLOCK; i < MAX_BLOCKS; i++) {
        if (metadata->freeBlocks[i] == 1 && count != 0) {
            if (count == requiredBlocks) {
                startBlock = i;
            }
            count--;
        } else if (count == 0) {
            break;
        } else {
            count = requiredBlocks;
        }
    }

    //fragmentation
    if (count != 0) {
        return 0;
    }

    for (i = startBlock; i < startBlock + requiredBlocks; i++) {
        metadata->freeBlocks[i] = 0;
    }

    return startBlock;
}

int copyToDisk(char *src, char *dest, Metadata *metadata) {

//    FILE * disk = open_file(filename, "rb+");

    int i, fileSize = getFilesize(src);
    int requiredBlocks = fileSize / BLOCK_SIZE + 1;
    int start = getFileStart(metadata, requiredBlocks);

    int wasAddedToMetadata = addEntryToMetadata(metadata, dest, start, requiredBlocks, fileSize);

    if (!wasAddedToMetadata) {
        return 0;
    }
    metadata->freeSpace -= fileSize;
    writeMetadataToFile(metadata);

    void * buffer = malloc(sizeof(void) * BLOCK_SIZE * requiredBlocks);
//    fseek(disk, start * BLOCK_SIZE, SEEK_SET);

    FILE * source = open_file(src, "rb");
    i = 0;
    while (fread(&buffer[i], sizeof(void), BLOCK_SIZE, source) != 0) {
        i += BLOCK_SIZE;
    }

    for (i = 0; i < requiredBlocks; i++) {
        write_block(&buffer[i * BLOCK_SIZE], start + i);
    }

    close_file(source);
    return 1;
}

int getIndexOfFile(char * file, Metadata * metadata) {
    int i = 0;
    while(strcmp(file, metadata->files[i].name) != 0) {
        i++;
    }
    return i;
}

int copyFromDisk(char *src, char *dest, Metadata *metadata) {
//    FILE * disk = open_file(filename, "rb");

    int index = getIndexOfFile(src, metadata);
    int requiredBlocks = metadata->files[index].noOfBlocks;
    int bytesToWrite = metadata->files[index].fileLength;
    int i = 0;
    int start = metadata->files[index].start;

    void * buffer = malloc(sizeof(void) * requiredBlocks * BLOCK_SIZE);

    FILE * d = open_file(dest, "wb");

    while (i < requiredBlocks) {
        void * readBlock = read_block(start + i);
        memcpy(&buffer[i * BLOCK_SIZE], readBlock, BLOCK_SIZE);
        i++;
    }

    write_file(buffer, sizeof(void), bytesToWrite, d);
    close_file(d);

    printf("Copied %d\n", metadata->files[index].fileLength);
    return 1;
}

int doesFileExist(char * src, Metadata * metadata) {
    int i;
    for (i = 0; i < metadata->tableSize; i++) {
        if (strcmp(metadata->files[i].name, src) == 0) {
            return i;
        }
    }
    return -1;
}

int deleteFileFromDisk(char * src, Metadata * metadata) {
    int i;
    int fileIndex = doesFileExist(src, metadata);
    if (fileIndex == -1) {
        printf("File doesn't exist\n");
        return -1;
    }

    metadata->freeSpace += metadata->files[fileIndex].fileLength;

    for (i = metadata->files[fileIndex].start; i < metadata->files[fileIndex].noOfBlocks + metadata->files[fileIndex].start; i++) {
        metadata->freeBlocks[i] = 1;
    }

    metadata->files[fileIndex].fileLength = metadata->files[metadata->tableSize - 1].fileLength;
    metadata->files[fileIndex].noOfBlocks = metadata->files[metadata->tableSize - 1].noOfBlocks;
    metadata->files[fileIndex].start = metadata->files[metadata->tableSize - 1].start;
    strcpy(metadata->files[fileIndex].name, metadata->files[metadata->tableSize - 1].name);

    metadata->tableSize--;

    writeMetadataToFile(metadata);

    printf("Deleted %s successfully\n", src);
    return 1;
}

void debugPrint(Metadata * metadata) {
    /*
     * typedef struct Metadata {
    unsigned int startKey;
    TableEntry files[MAX_TABLE_SIZE];
    unsigned int tableSize;
    char freeBlocks[MAX_BLOCKS];
    unsigned int freeSpace;
}Metadata;
     */
    printf("START KEY = %c %c %c %c\n", metadata->startKey);
    printf("NUMBER OF FILES = %d\n", metadata->tableSize);
    printf("FREE SPACE(IN BYTES) = %d\n", metadata->freeSpace);
    int i;
    for(i = 0; i < metadata->tableSize; i++) {
        printf("FILE %d : %s %d %d %d\n",
                i + 1,
                metadata->files[i].name,
                metadata->files[i].start,
                metadata->files[i].noOfBlocks,
                metadata->files[i].fileLength
                );
    }
}

void formatDisk() {
    writeMetadataToFile(createMetadataTable());
    printf("Formatted!\n");
}


void take_command(Metadata * metadata) {
    while (1) {
        char s[32];
        scanf(" %s", s);
        if (strcasecmp(s, "copytodisk") == 0) {

            char arg1[16], arg2[16];
            scanf(" %s %s", arg1, arg2);
            copyToDisk(arg1, arg2, metadata);

        } else if (strcasecmp(s, "list") == 0) {

            listFiles(metadata);

        } else if (strcasecmp(s, "copyfromdisk") == 0) {

            char arg1[16], arg2[16];
            scanf(" %s %s", arg1, arg2);
            copyFromDisk(arg1, arg2, metadata);

        } else if(strcasecmp(s, "exit") == 0) {

            break;

        } else if (strcasecmp(s, "format") == 0) {

            formatDisk();
            free(metadata);
            metadata = createMetadataTable();
        } else if (strcasecmp(s, "delete") == 0) {

            char arg[32];
            scanf(" %s", arg);
            deleteFileFromDisk(arg, metadata);

        } else if (strcasecmp(s, "debug") == 0) {

            debugPrint(metadata);

        } else if (strcasecmp(s, "init") == 0) {

            unsigned int blocksize;
            char diskName[30];

            scanf(" %s %d", diskName, &blocksize);
            initDisk(diskName, blocksize);

        } else {

                printf("Command not found\n");

        }
    }
}
