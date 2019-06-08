//
// Created by harsha on 2019-05-27.
//

#ifndef EXCEL_IMPORT_H
#define EXCEL_IMPORT_H

#include "utils.h"
#include "state.h"
#include "exceptions.h"

cell *** get_data_from_file(char * filename);
void save_data_to_state(cell *** oldstate, cell *** new_state_data);

#endif //EXCEL_IMPORT_H
