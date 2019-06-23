//
// Created by harsha on 2019-06-02.
//

#ifndef FSYSTEM_EXT_COMPILER_H
#define FSYSTEM_EXT_COMPILER_H

#include <stdio.h>
#include "../utils.h"
#include "parsing.h"
#include <string.h>
#include <stdlib.h>
#include "my_stack.h"

void printSymbolTable(symbolTable * table);
char ** run_compiler(char ** lines, int inpLines, int * returnLength);
void printBlockTable(BlockTable * blocktable);

#endif //FSYSTEM_EXT_COMPILER_H
