#include <stdio.h>
#include "structure.h"
#include "fscommands.h"

void run_fs() {
    Metadata * metadata = createMetadataTable();
//    addEntryToMetadata(metadata, "abcd", 1000, 2, 10);
//    addEntryToMetadata(metadata, "abcd", 1000, 2, 10);
//    addEntryToMetadata(metadata, "abcd", 1000, 2, 10);
//    addEntryToMetadata(metadata, "abcd", 1000, 2, 10);
//    addEntryToMetadata(metadata, "abcd", 1000, 2, 10);
//    clearDisk();
    metadata = initMetadata();
//    writeMetadataToFile(metadata);
    take_command(metadata);
}

int main() {
    run_fs();
    return 0;
}
