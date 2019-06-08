//
// Created by harsha on 2019-05-30.
//

#ifndef FSYSTEM_FSCOMMANDS_H
#define FSYSTEM_FSCOMMANDS_H

#include "structure.h"

//utils
void close_file(FILE * f);
FILE * open_file(const char * name, const char * mode);
void write_file(void * ptr, size_t size, size_t n_el, FILE * f);

//fscommands
Metadata * createMetadataTable();
Metadata * initMetadata();
void listFiles (Metadata * metadata);
void writeMetadataToFile(Metadata * toWrite);
int copyToDisk(char *src, char *dest, Metadata *metadata);
int getIndexOfFile(char * file, Metadata * metadata);
int copyFromDisk(char *src, char *dest, Metadata *metadata);
int deleteFileFromDisk(char * src, Metadata * metadata);
void debugPrint(Metadata * metadata);
void formatDisk ();
//UI
void take_command(Metadata * metadata);


#endif //FSYSTEM_FSCOMMANDS_H
