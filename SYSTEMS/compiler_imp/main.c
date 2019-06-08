#include <stdio.h>
#include "fileio.h"
#include "parsing.h"
#include <string.h>
#include <stdlib.h>
#include "my_stack.h"

void printSymbolTable(symbolTable * table) {
    int i;
    for (i = 0; i < table->tableSize; i++) {
        printf("%s %d %d\n", table->symbols[i].symbol, table->symbols[i].address, table->symbols[i].size);
    }
}

void printBlockTable(BlockTable * blocktable) {
    int i;
    for (i = 0; i < blocktable->tableSize; i++) {
        printf(" %s %d \n", blocktable->blocks[i].blockName, blocktable->blocks[i].address);
    }
    printf("\n");
}

int run_compiler(const char * inputfile, char * outputfile) {
    int i, address = 0;

    BlockTable * blockTable = (BlockTable *)malloc(sizeof(BlockTable));
    blockTable->blocks = NULL;
    blockTable->tableSize = 0;

    symbolTable * table = (symbolTable *)malloc(sizeof(symbolTable));
    table->tableSize = 0;
    table->symbols = NULL;
    int * codes = malloc(sizeof(int) * 6);

    stack * backFill = create_stack(1000);

    FILE * inputProgramFile = open_file(inputfile, "r");
    int ** compiledProgram = (int **)malloc(sizeof(int *) * 1000);
    int numberCodesEachLine[1000];
    int numberOfLinesOfCompiledProgram = 0;

    while(feof(inputProgramFile) == 0) {
        char * line = readLine(inputProgramFile);
        char ** tokens = tokenize(line);

        if (tokens[0] == NULL) continue;

        if (strcasecmp(tokens[0], "DATA") == 0 || strcasecmp(tokens[0], "CONST") == 0) {
            buildSymbolTable(tokens, table, address);
            address++;

        } else if (strcasecmp("START:", tokens[0]) == 0) {
            //skip
        }
        //block
        else if (strstr(tokens[0], ":") != NULL){
            processBlock(tokens[0], numberOfLinesOfCompiledProgram + 1, blockTable);
        }
        else if (strcasecmp(tokens[0], "END") == 0) {
            //EOF
            break;
        }
        else if (strcasecmp(tokens[0], "IF")  == 0 || strcasecmp(tokens[0], "ELSE") == 0) {
            int numberofcodes;
            int index = numberOfLinesOfCompiledProgram;
            compiledProgram[index] = (int *)malloc(sizeof(int) * 6);

            if (tokens[0][0] == 'I' || tokens[0][0] == 'i') {
                numberofcodes = processIf(tokens, table, codes);

            } else {
                numberofcodes = processElse(tokens, codes);
                processBlock("ELSE", numberOfLinesOfCompiledProgram, blockTable);
            }

            memcpy(compiledProgram[index], codes, numberofcodes * sizeof(int));
            numberCodesEachLine[index] = numberofcodes;
            push(backFill, numberOfLinesOfCompiledProgram);
            numberOfLinesOfCompiledProgram++;
        }
        else if (strcasecmp("ENDIF", tokens[0]) == 0) {
            processEndif(compiledProgram, backFill, numberOfLinesOfCompiledProgram + 1);
        }
        else if (strcasecmp("JMP", tokens[0]) == 0) {
            int index = numberOfLinesOfCompiledProgram;
            compiledProgram[index] = (int *)malloc(sizeof(int) * 6);
            int numberofcodes = processJump(tokens, blockTable, codes);
            memcpy(compiledProgram[index], codes, numberofcodes * sizeof(int));
            numberCodesEachLine[index] = numberofcodes;
            numberOfLinesOfCompiledProgram++;
        }
        else {
            int index = numberOfLinesOfCompiledProgram;
            compiledProgram[index] = (int *)malloc(sizeof(int) * 6);
            int numberofcodes = processProgramInstruction(tokens, table, codes);
            memcpy(compiledProgram[index], codes, numberofcodes * sizeof(int));
            numberCodesEachLine[index] = numberofcodes;
            numberOfLinesOfCompiledProgram++;
        }
    }


    FILE * outputFile = open_file(outputfile, "w");

    for(i = 0; i < numberOfLinesOfCompiledProgram; i++) {
        int k;
        for (k = 0; k < numberCodesEachLine[i]; k++) {
            fprintf(outputFile, "%d ", compiledProgram[i][k]);
        }
        fprintf(outputFile, "\n");
    }

    //TODO Write to output file instead of console
    printBlockTable(blockTable);
    printSymbolTable(table);

    close_file(outputFile);
    close_file(inputProgramFile);

    return 1;
}




int main() {
    run_compiler("abc.txt", "acde.txt");
    return 0;
}
