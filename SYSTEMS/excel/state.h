//
// Created by harsha on 2019-05-27.
//

#ifndef EXCEL_STATE_H
#define EXCEL_STATE_H

#include <stdlib.h>
#include "utils.h"
#include "cell_structure.h"

#define ROWS 10
#define COLUMNS 10

cell *** create_singleton_state();
void write_to_singleton_state(cell *** oldstate, cell *** newstate);
int ** copy_state(int ** state);
void clear_state(int ** state);

#endif //EXCEL_STATE_H
