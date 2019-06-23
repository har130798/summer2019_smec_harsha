#include <stdio.h>
#include "structure.h"
#include "fscommands.h"
#include "compiler/compiler.h"

void run_fs() {
    Metadata * metadata = createMetadataTable();
//    formatDisk();
//    writeMetadataToFile(metadata);
    metadata = initMetadata();
    take_command(metadata);
}

int main() {
    run_fs();
    return 0;
}
