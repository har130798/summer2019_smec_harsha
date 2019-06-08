//
// Created by harsha on 2019-06-01.
//

#include "constants.h"
#include <string.h>
#include <stdlib.h>

int getOpcode(const char * instruction) {
    char * opcode = (char *)malloc(sizeof(char) * 10);
    if (strcmp("MOV1", instruction) == 0) {
        return 1;
    }
    else if (strcmp("MOV2", instruction) == 0) {
        return 2;
    }
    else if (strcmp("ADD", instruction) == 0) {
        return 3;
    }
    else if (strcmp("SUB", instruction) == 0) {
        return 4;
    }
    else if (strcmp("MUL", instruction) == 0) {
        return 5;
    }
    else if (strcmp("JMP", instruction) == 0) {
        return 6;
    }
    else if (strcmp("IF", instruction) == 0) {
        return 7;
    }
    else if (strcmp("EQ", instruction) == 0) {
        return 8;
    }
    else if (strcmp("LT", instruction) == 0) {
        return 9;
    }
    else if (strcmp("GT", instruction) == 0) {
        return 10;
    }
    else if (strcmp("LTEQ", instruction) == 0) {
        return 11;
    }
    else if (strcmp("GTEQ", instruction) == 0) {
        return 12;
    }
    else if (strcmp("PRINT", instruction) == 0) {
        return 13;
    }
    else if (strcmp("READ", instruction) == 0) {
        return 14;
    }
    else if (strcmp("THEN", instruction) == 0) {
        return 15;
    }
    else if (strcmp("ENDIF", instruction) == 0) {
        return 16;
    }
    else {
        return -1;
    }
}

char * getRegistercode(char * registername) {
    char * code = (char *)malloc(sizeof(char) * 3);
    if (strcasecmp("AX", registername) == 0) {
        strcpy(code, "00");
    }
    else if (strcasecmp("BX", registername) == 0) {
        strcpy(code, "01");
    }
    else if (strcasecmp("CX", registername) == 0) {
        strcpy(code, "02");
    }
    else if (strcasecmp("DX", registername) == 0) {
        strcpy(code, "04");
    }
    else if (strcasecmp("EX", registername) == 0) {
        strcpy(code, "05");
    }
    else if (strcasecmp("FX", registername) == 0) {
        strcpy(code, "06");
    }
    else if (strcasecmp("HX", registername) == 0) {
        strcpy(code, "07");
    }
    else {
        return NULL;
    }
    return code;
}