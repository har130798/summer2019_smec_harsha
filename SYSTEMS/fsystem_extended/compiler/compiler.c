//
// Created by harsha on 2019-06-02.
//

#include "compiler.h"

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

char * intToChar(int num) {
    char * n = (char *)malloc(sizeof(char) * 20);
    int k = 0;
    do {
        int rem = num % 10;
        num /= 10;
        n[k++] = rem + 48;
    } while(num > 0);

    n[k] = 0;

    char * reverse = (char *)malloc(sizeof(char) * 20);
    int i;
    for (i = k - 1; i >= 0; i--) {
        reverse[k - 1 - i] = n[i];
    }
    reverse[k] = 0;
    free(n);
    n = NULL;
    return reverse;
}

char ** joinMatrix(int ** matrix, int rows, int * columnsInEachRow) {
    char ** joined = (char **)malloc(sizeof(char *) * rows);
    int i, j;
    for (i = 0; i < rows; i++) {
        joined[i] = (char *)malloc(sizeof(char) * 100);
        int copied = 0;
        for (j = 0; j < columnsInEachRow[i]; j++) {
            char * num = intToChar(matrix[i][j]);
            memcpy(&joined[i][copied], num, strlen(num));
            copied += strlen(num);
            joined[i][copied] = ' ';
            copied ++;
        }
        joined[i][copied - 1] = '\n';
        joined[i][copied] = 0;
    }
    return joined;
}

char ** run_compiler(char ** lines, int inpLines, int * returnLength) {
    int i, address = 0;

    BlockTable * blockTable = (BlockTable *)malloc(sizeof(BlockTable));
    blockTable->blocks = NULL;
    blockTable->tableSize = 0;

    symbolTable * table = (symbolTable *)malloc(sizeof(symbolTable));
    table->tableSize = 0;
    table->symbols = NULL;
    int * codes = malloc(sizeof(int) * 6);

    stack * backFill = create_stack(1000);

//    FILE * inputProgramFile = open_file(inputfile, "r");
    int ** compiledProgram = (int **)malloc(sizeof(int *) * 1000);
    int numberCodesEachLine[1000];
    int numberOfLinesOfCompiledProgram = 0;

    int toRead = 0;

    while(toRead < inpLines) {
        char * line = lines[toRead++];
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
            if (numberofcodes == -1) continue;
            memcpy(compiledProgram[index], codes, numberofcodes * sizeof(int));
            numberCodesEachLine[index] = numberofcodes;
            numberOfLinesOfCompiledProgram++;
        }
    }

    //TODO Write to output file instead of console
//    printBlockTable(blockTable);
//    printSymbolTable(table);

    *returnLength = numberOfLinesOfCompiledProgram;
    char ** mat = joinMatrix(compiledProgram, numberOfLinesOfCompiledProgram, numberCodesEachLine);

    return mat;
}
