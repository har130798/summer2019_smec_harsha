//
// Created by harsha on 2019-06-01.
//

#ifndef COMPILER_PARSING_H
#define COMPILER_PARSING_H

#include "my_stack.h"

typedef struct symbol {
    char symbol[24];
    unsigned int address;
    unsigned int size;
}symbol;

typedef struct symbolTable {
    unsigned int tableSize;
    symbol * symbols;
}symbolTable;

typedef struct Block {
    char blockName[28];
    unsigned int address;
}Block;

typedef struct BlockTable {
    unsigned int tableSize;
    Block * blocks;
}BlockTable;

char ** tokenize(const char * line);
void buildSymbolTable(char ** tokens, symbolTable * table, int address);
int processProgramInstruction(char ** tokens, symbolTable * table, int * codes);
void processBlock(char * blockName, unsigned int address, BlockTable * blockTable);
int processIf(char ** tokens, symbolTable * table, int * codes);
int processElse (char ** tokens, int * codes);
void processEndif(int ** program, stack * backfill, int lineNumber);
int processJump(char ** tokens, BlockTable * blockTable, int * codes);

#endif //COMPILER_PARSING_H
