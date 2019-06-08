//
// Created by harsha on 2019-06-01.
//

#include "parsing.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char ** tokenize(const char * line) {
    int i, j = 0, k;
    char ** tokens = (char **)malloc(sizeof(char *) * 6);
    char * linecopy = (char *)malloc(sizeof(char) * 100);
    strcpy(linecopy, line);

    char delimiters[5] = ", \n";

    char* rest = linecopy;
    char * token = strtok_r(rest, delimiters, &rest);

    while (token != NULL) {
        tokens[j] = (char *)malloc(sizeof(char) * 100);
        strcpy(tokens[j++], token);
        token = strtok_r(rest, delimiters, &rest);
    }

    return tokens;
}

int isArray(const char * arg) {
    int i = 0;
    while (arg[i] && arg[i] != '[') {
        i++;
    }

    if (arg[i] != '[') return -1;
    else return i + 1;
}

void buildSymbolTable(char ** tokens, symbolTable * table, int address) {
    int i = table->tableSize;
    if (i == 0) {
        table->symbols = (symbol *)malloc(sizeof(symbol));
    } else {
        table->symbols = realloc(table->symbols, sizeof(symbol) * (i + 1));
    }

    if (strcasecmp(tokens[0], "DATA") == 0) {
        table->symbols[i].address = address;
        if (strstr(tokens[1], "[") != NULL) {
            int j = 0;
            while(tokens[1][j] != '[') {
                table->symbols[i].symbol[j] = tokens[1][j];
                j++;
            }
            table->symbols[i].symbol[j] = 0;
            table->symbols[i].size = 0;
            j++;
            while(tokens[1][j] != ']') {
                table->symbols[i].size = table->symbols[i].size * 10 + tokens[1][j] - 48;
                j++;
            }
        } else {
            strcpy(table->symbols[i].symbol, tokens[1]);
            table->symbols[i].size = 1;
        }


    } else if (strcasecmp(tokens[0], "CONST") == 0) {
        table->symbols[i].address = address;
        strcpy(table->symbols[i].symbol, tokens[1]);
        table->symbols[i].size = 0;
        //TODO save value in memory
    }
    table->tableSize++;
}

int isRegister(char * token) {
    int i = 0;

    if (strlen(token) != 2) {
        return 0;
    }
    if (strcasestr("AXBXCXDXEXDXFXGXHX", token) == NULL) return 0;
    return 1;
}

int getSymbolAddress(char * token, symbolTable * table) {
    int i;
    for (i = 0; i < table->tableSize; i++) {
        if (strcasecmp(token, table->symbols[i].symbol) == 0) {
            return table->symbols[i].address;
        }
    }
    return -1;
}

int processArithmetic(char ** tokens, symbolTable * table, int * codes) {
    char * ins = tokens[0];
    if (strcasecmp(ins, "ADD") == 0) {
        codes[0] = 3;
    } else if (strcasecmp(ins, "SUB") == 0) {
        codes[0] = 4;
    } else if (strcasecmp(ins, "MUL") == 0){
        codes[0] = 5;
    } else {
        return 0;
    }
    int i;
    for (i = 1; i < 4; i++) {
        codes[i] = isRegister(tokens[i]) ? tokens[i][0] - 65 : getSymbolAddress(tokens[i], table);
    }

    return 4;
}

int processMove(char ** tokens, symbolTable * table, int * codes) {
    codes[0] = isRegister(tokens[1]) ? getOpcode("MOV2") : getOpcode("MOV1");

    if (codes[0] == 1) {
        codes[1] = getSymbolAddress(tokens[1], table);
        codes[2] = tokens[2][0] - 65;
    } else {
        codes[1] = tokens[1][0] - 65;
        codes[2] = getSymbolAddress(tokens[2], table);
    }

    return 3;
}

int processRead(char ** tokens, int * codes) {
    codes[0] = getOpcode(tokens[0]);
    codes[1] = tokens[1][0] - 65;
    return 2;
}

int processPrint(char ** tokens, symbolTable * table, int * codes) {
    codes[0] = getOpcode(tokens[0]);
    codes[1] = getSymbolAddress(tokens[1], table);
    return 2;
}

void processBlock(char * blockName, unsigned int address, BlockTable * blockTable) {
    if (blockName[strlen(blockName) - 1] == ':') {
        blockName[strlen(blockName) - 1] = 0;
    }
    if (blockTable->tableSize == 0) {
        blockTable->tableSize = 1;
        blockTable->blocks = (Block *)malloc(sizeof(Block));
        strcpy(blockTable->blocks[0].blockName, blockName);
        blockTable->blocks[0].address = address;
        return;
    }

    blockTable->blocks = realloc(blockTable->blocks, blockTable->tableSize + 1);
    int prevSize = blockTable->tableSize;
    blockTable->blocks[prevSize].address = address;
    strcpy(blockTable->blocks[prevSize].blockName, blockName);
    blockTable->tableSize++;
}

int processIf(char ** tokens, symbolTable * table, int * codes) {
    int i = 0;
    codes[i++] = getOpcode(tokens[0]);
    codes[i++] = isRegister(tokens[1]) ? tokens[1][0] - 65 : getSymbolAddress(tokens[1], table);
    codes[i++] = getOpcode(tokens[2]);
    codes[i++] = isRegister(tokens[3]) ? tokens[3][0] - 65 : getSymbolAddress(tokens[3], table);
    codes[i++] = -1;
    return 5;
}

int processElse (char ** tokens, int * codes) {
    codes[0] = getOpcode("JMP");
    codes[1] = -1;
    return 2;
}

void processEndif(int ** program, stack * backfill, int lineNumber) {
    int poppedVal = pop(backfill);
    if (getOpcode("IF") == program[poppedVal][0]) {
        //if block
        program[poppedVal][4] = lineNumber;
    } else {
        program[poppedVal][1] = lineNumber;
        int nextpoppedVal = pop(backfill);
        program[nextpoppedVal][4] = poppedVal;
    }
}

int getAddressOfLabelFromBlockTable(BlockTable * table, char * label) {
    int i;
    for (i = 0; i < table->tableSize; i++) {
        if (strcmp(label, table->blocks[i].blockName) == 0) {
            return table->blocks[i].address;
        }
    }
    return -1;
}

int processJump(char ** tokens, BlockTable * blockTable, int * codes) {
    codes[0] = getOpcode("JMP");
    codes[1] = getAddressOfLabelFromBlockTable(blockTable, tokens[1]);
    return 2;
}

int processProgramInstruction(char ** tokens, symbolTable * table, int * codes) {
    char * ins = tokens[0];

    if (strcasecmp(ins, "ADD") == 0 || strcasecmp(ins, "SUB") == 0 || strcasecmp(ins, "MUL") == 0) {
        return processArithmetic(tokens, table, codes);
    } else if (strcasecmp(ins, "MOV") == 0) {
        return processMove(tokens, table, codes);
    } else if (strcasecmp(ins, "READ") == 0) {
        return processRead(tokens, codes);
    } else if (strcasecmp(ins, "PRINT") == 0) {
        return processPrint(tokens, table, codes);
    }
    return -1;
}

//int getConstVal(const char * arg) {
//    int i = 0;
//    while(arg[i] != '=') {
//        i++;
//    }
//    char val[20];
////    strcpy(val, )
//    return i + 1;
//}
//
//void parseDeclarationLine(const char * line, symbolTable * table, int * address) {
//    int i = 0, k = 0;
//    char * ins = (char *)malloc(sizeof(char) * 10);
//    char * codegen = (char *)malloc(sizeof(char) * 1000);
//
//    //skip spaces at begin
//    while (line[i] == ' ') {
//        i++;
//    }
//
//    //read instruction
//    while (line[i] != ' ') {
//        ins[k++] = line[i];
//        i++;
//    }
//    ins[k] = 0;
//
//    char * var = (char *)malloc(sizeof(char) * 20);
//    k = 0;
//    while (line[i]){
//        var[k++] = line[i];
//        i++;
//    }
//    var[k] = 0;
//
//
//    if (strcmp("DATA", ins) == 0) {
//        int isarr = isArray(var);
//        if (isarr != -1) {
//            int index = 0, lim = var[isarr] - 48;
//            if (lim == 0) return;
//            while(lim--) {
//                var[isarr] = 48 + index;
//                table->symbols[table->tableSize].address = *address;
//                strcpy(table->symbols[table->tableSize].symbol, var);
//                table->tableSize++;
//                *address = *(address) + 1;
//            }
//        }
//        else {
//            table->symbols[table->tableSize].address = *address;
//            strcpy(table->symbols[table->tableSize].symbol, var);
//            table->tableSize++;
//        }
//    } else {
//        table->symbols[table->tableSize].address = *address;
//        char val[20];
////        strcpy(val, var[getConstVal()])
////        table->symbols[table->tableSize].constVal = atoi()
//        strcpy(table->symbols[table->tableSize].symbol, var);
//        table->tableSize++;
//    }
//}

//symbolTable * parseAllDeclarationLines(char ** lines) {
//    int curAddress = 0x0000;
//    int i = 0;
//    char * line;
////    while(strcasecmp(lines[i], "START:") != 0) {
//////        parseDeclarationLine(lines[i]);
////    }
//}

