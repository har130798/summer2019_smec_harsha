//
// Created by harsha on 2019-05-31.
//

#include "fscommands.h"
#include "diskIO.h"
#include "structure.h"
#include "utils.h"
#include "compiler/compiler.h"

Metadata * createMetadataTable() {
    Metadata * metadata = (Metadata *)malloc(sizeof(Metadata));

    metadata->startKey = START_KEY;
    metadata->tableSize = 0;
    metadata->freeBlockCount = MAX_BLOCKS;

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

void writeMetadataToFile(Metadata * toWrite) {
    int i, blocksRequired = sizeof(Metadata) / BLOCK_SIZE;
    if (sizeof(Metadata) % BLOCK_SIZE != 0) blocksRequired += 1;

    void * buffer = malloc(sizeof(Metadata));
    memcpy(buffer, toWrite, sizeof(Metadata));

    for (i = 0; i < blocksRequired; i++) {
        write_block(&buffer[i* BLOCK_SIZE], i);
    }
}

unsigned int * getFileStart(Metadata *metadata, int requiredBlocks) {
    int i, count = requiredBlocks;
    unsigned int startBlock = 0;

    //No sufficient space available
    if (metadata->freeBlockCount <= requiredBlocks) return 0;

    unsigned int * blockLocations = (unsigned int *)malloc(sizeof(unsigned int) * requiredBlocks);

    int k = 0;
    for(i = START_BLOCK; i < MAX_BLOCKS && count; i++) {
        if (metadata->freeBlocks[i] == 1) {
            metadata->freeBlocks[i] = 0;
            metadata->freeBlockCount--;
            blockLocations[k++] = i;
            count--;
        }
    }

    return blockLocations;
}

int copyToDisk(char *src, char *dest, Metadata *metadata) {

//    FILE * disk = open_file(filename, "rb+");

    int i, fileSize = getFilesize(src);
    int requiredBlocks;
    if (fileSize / BLOCK_SIZE == 0) {
        requiredBlocks = 1;
    } else {
        if (fileSize % BLOCK_SIZE == 0) {
            requiredBlocks = fileSize / BLOCK_SIZE;
        } else {
            requiredBlocks = fileSize / BLOCK_SIZE + 1;
        }
    }

    requiredBlocks = requiredBlocks == 1 ? 1 : requiredBlocks + 1;
    unsigned int * start = getFileStart(metadata, requiredBlocks);

    if (start == 0) {
        printf("Couldn't add file \n");
        return -1;
    }

    int wasAddedToMetadata = addEntryToMetadata(metadata, dest, start[0], requiredBlocks, fileSize);

    if (!wasAddedToMetadata) {
        return 0;
    }
    writeMetadataToFile(metadata);

    if (requiredBlocks == 1) {
        void * buffer = malloc(sizeof(void) * BLOCK_SIZE);
        FILE * source = open_file(src, "rb");
//        i = 0;
        fread(buffer, sizeof(void), fileSize, source);
//        while (fread(&buffer[i], sizeof(void), 1, source) != 0) {
//            i++;
//        }

        write_block(buffer, start[0]);
        close_file(source);
    } else {
        void * buffer = malloc(sizeof(void) * BLOCK_SIZE);
        memcpy(buffer, start + 1, requiredBlocks * sizeof(unsigned int));
        write_block(buffer, start[0]);
        requiredBlocks--;

        buffer = malloc(sizeof(void) * BLOCK_SIZE * requiredBlocks);

        FILE * source = open_file(src, "rb");
        i = 0;
        while (fread(&buffer[i], sizeof(void), BLOCK_SIZE, source) != 0) {
            i += BLOCK_SIZE;
        }

        for (i = 0; i < requiredBlocks; i++) {
            write_block(&buffer[i * BLOCK_SIZE], start[i + 1]);
        }

        close_file(source);
    }

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
    int start = metadata->files[index].start;

    FILE * d = open_file(dest, "wb");
    void * buffer;

    if (requiredBlocks == 1) {
        void * readBlock = read_block(start);
        write_file(readBlock, sizeof(void), bytesToWrite, d);
        printf("Copied %d\n", metadata->files[index].fileLength);
        close_file(d);
        return 1;
    }

    requiredBlocks--;
    unsigned int * blockLocations = (unsigned int *)malloc(sizeof(unsigned int) * requiredBlocks);
    memcpy(blockLocations, read_block(start), requiredBlocks * sizeof(unsigned int));

    buffer = malloc(sizeof(void) * requiredBlocks * BLOCK_SIZE);

    int i = 0;
    while (i < requiredBlocks) {
        void * readBlock = read_block(blockLocations[i]);
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

    unsigned int start = metadata->files[fileIndex].start;
    metadata->freeBlockCount += metadata->files[fileIndex].noOfBlocks;

    int requiredBlocksToClear = metadata->files[fileIndex].noOfBlocks;
    if (requiredBlocksToClear == 1) {
        metadata->freeBlocks[metadata->files[fileIndex].start] = 1;
    } else {
        requiredBlocksToClear--;
        unsigned int * blockLocations = (unsigned int *)malloc(sizeof(unsigned int) * requiredBlocksToClear);
        memcpy(blockLocations, read_block(start), requiredBlocksToClear * sizeof(unsigned int));
        metadata->freeBlocks[start] = 1;
        for (i = 0; i < requiredBlocksToClear; i++) {
            metadata->freeBlocks[blockLocations[i]] = 1;
        }
    }

    if (metadata->tableSize == 1) {
        metadata = createMetadataTable();
        writeMetadataToFile(metadata);

        printf("Deleted %s successfully\n", src);
        return 1;
    } else {
        metadata->files[fileIndex].fileLength = metadata->files[metadata->tableSize - 1].fileLength;
        metadata->files[fileIndex].noOfBlocks = metadata->files[metadata->tableSize - 1].noOfBlocks;
        metadata->files[fileIndex].start = metadata->files[metadata->tableSize - 1].start;
        strcpy(metadata->files[fileIndex].name, metadata->files[metadata->tableSize - 1].name);
    }

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
    unsigned int freeBlockCount;
}Metadata;
     */
    printf("START KEY = %c %c %c %c\n", metadata->startKey);
    printf("NUMBER OF FILES = %d\n", metadata->tableSize);
    printf("FREE BLOCKS = %d\n", metadata->freeBlockCount);
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

void * convertToByteStream(char ** data, int datarows, int * length) {
    int i, k = 0;
    int max = BLOCK_SIZE;
    void * buffer = (char *)malloc(sizeof(void) * max);
    for (i = 0; i < datarows; i++) {
        int j = 0;
        while (data[i][j]) {
            if (k == max) {
                max *= 2;
                buffer = realloc(buffer, max);
            }
            memcpy(&buffer[k++], &data[i][j++], 1);
        }
        if (k == max) {
            max *= 2;
            buffer = realloc(buffer, max);
        }
        //possible bug here due to null char
//        memcpy(&buffer[k++], &data[i][j], 1);

    }
    *length = k;
    return buffer;
}

int compile(Metadata * metadata, char * srcfile, char * destfile) {

    //read program from fs
    int index = getIndexOfFile(srcfile, metadata);
    int requiredBlocks = metadata->files[index].noOfBlocks;
    int bytesToWrite = metadata->files[index].fileLength;
    int start = metadata->files[index].start;

    void * buffer;

    if (requiredBlocks == 1) {
        buffer = read_block(start);
    } else {
        requiredBlocks--;
        unsigned int * blockLocations = (unsigned int *)malloc(sizeof(unsigned int) * requiredBlocks);
        memcpy(blockLocations, read_block(start), requiredBlocks * sizeof(unsigned int));

        buffer = malloc(sizeof(void) * requiredBlocks * BLOCK_SIZE);

        int i = 0;
        while (i < requiredBlocks) {
            void * readBlock = read_block(blockLocations[i]);
            memcpy(&buffer[i * BLOCK_SIZE], readBlock, BLOCK_SIZE);
            i++;
        }
    }

    char * line;
    int linecount = 0;
    char ** lines = (char **) malloc(sizeof(char *) * 500);
    while((line = strtok_r((char *)buffer, "\n", &buffer)) != 0) {
        lines[linecount++] = line;
    }

    char ** toWrite = run_compiler(lines, linecount, &linecount);

    //write back to fs
    int i, fileSize = 0;

    void * dataBuffer = convertToByteStream(toWrite, linecount, &fileSize);

    if (fileSize / BLOCK_SIZE == 0) {
        requiredBlocks = 1;
    } else {
        if (fileSize % BLOCK_SIZE == 0) {
            requiredBlocks = fileSize / BLOCK_SIZE;
        } else {
            requiredBlocks = fileSize / BLOCK_SIZE + 1;
        }
    }

    requiredBlocks = requiredBlocks == 1 ? 1 : requiredBlocks + 1;
    unsigned int * startBlock = getFileStart(metadata, requiredBlocks);

    if (start == 0) {
        printf("Couldn't add file \n");
        return -1;
    }

    int wasAddedToMetadata = addEntryToMetadata(metadata, destfile, startBlock[0], requiredBlocks, fileSize);

    if (!wasAddedToMetadata) {
        return 0;
    }
    writeMetadataToFile(metadata);

    if (requiredBlocks == 1) {
        buffer = malloc(sizeof(void) * BLOCK_SIZE);
        memcpy(buffer, dataBuffer, fileSize);
        write_block(buffer, startBlock[0]);
    } else {
        buffer = malloc(sizeof(void) * BLOCK_SIZE);
        memcpy(buffer, startBlock + 1, requiredBlocks * sizeof(unsigned int));
        write_block(buffer, startBlock[0]);
        requiredBlocks--;

        buffer = malloc(sizeof(void) * BLOCK_SIZE * requiredBlocks);

        memcpy(buffer, dataBuffer, fileSize);

        for (i = 0; i < requiredBlocks; i++) {
            write_block(&buffer[i * BLOCK_SIZE], startBlock[i + 1]);
        }
    }
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

        } else if (strcasecmp(s, "compile") == 0) {

            char arg1[16], arg2[16];
            scanf(" %s %s", arg1, arg2);
            compile(metadata, arg1, arg2);

        }
//        else if (strcasecmp(s, "init") == 0) {
//
//            unsigned int blocksize;
//            char diskName[30];
//
//            scanf(" %s %d", diskName, &blocksize);
//            initDisk(diskName, blocksize);
//
//        }
        else {

            printf("Command not found\n");

        }
    }
}
