//
// Created by harsha on 2019-05-27.
//

#include "state.h"

cell *** create_singleton_state() {
    cell *** state = create_cell_grid();
    return state;
}

void write_to_singleton_state(cell *** oldstate, cell *** newstate) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for(j = 0; j < COLUMNS; j++){
            if(newstate[i][j]->expression != NULL) {
                oldstate[i][j]->expression = create_string(strlen(newstate[i][j]->expression));
                strcpy(oldstate[i][j]->expression, newstate[i][j]->expression);
            } else {
                strcpy(oldstate[i][j]->val, newstate[i][j]->val);
            }
        }
    }
}
