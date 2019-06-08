//
// Created by harsha on 2019-05-27.
//

#include "import.h"

cell *** get_data_from_file(char * filename) {
    int i, j = 0, headers = 0;

    if (strcasestr(filename, "headers=true")){
        char * file = create_string(strlen(filename));
        i = strlen(filename) - 1;
        while(filename[i] != 'h') {
            i--;
        }
        filename[i] = 0;
        strcpy(file, filename);
        headers = 1;
    }
    FILE * f = open_file(filename, "r");
    if (f == NULL) {
        return NULL;
    }
    char * input = create_string(100);
    char * buffer = create_string(100);
    cell *** mat = create_cell_grid();

    for (i = -1; i < ROWS; i++) {
        fgets(input, 10 * ROWS, f);
        if (headers && i == -1) {
            continue;
        } else if (!headers && i == -1){
            i = 0;
        }
        int k = 0, mat_y = -1;
        while(1) {
            if (input[k] == ',' ){
                buffer[j] = 0;
                if (headers && mat_y == -1) {
                    mat_y = 0;
                    j = 0;
                    k++;
                    continue;
                } else if (!headers && mat_y == -1) mat_y = 0;
                strcpy(mat[i][mat_y++]->val,buffer);
                j = 0;
            } else if (input[k] == '\r' || input[k] == 0) {
                break;
            } else {
                buffer[j++] = input[k];
            }
            k++;
        }
        buffer[j] = 0;
        strcpy(mat[i][mat_y++]->val,buffer);
        j = 0;
    }
    close_file(f);

    return mat;
}

void save_data_to_state(cell *** oldstate, cell *** new_state_data) {
    if (new_state_data == NULL) {
        print_file_not_found_exception();
        return;
    }

    write_to_singleton_state(oldstate, new_state_data);
}
