//
// Created by harsha on 2019-05-27.
//

#ifndef EXCEL_CONTROLLER_H
#define EXCEL_CONTROLLER_H

#include <stdbool.h>

#include "utils.h"
#include "state.h"
#include "export.h"
#include "GET.h"
#include "SET.h"
#include "import.h"
#include "exceptions.h"
#include "PRINT.h"

cell *** init_app();
int run_app(cell *** state); //return 1 to kill
void kill_app(cell *** state); // 1 for set 2 for get etc
int execute_command(cell *** state); // 1 for set 2 for get etc
char * print_output(char * toPrint);
char ** parse_command(char * input);

#endif //EXCEL_CONTROLLER_H
