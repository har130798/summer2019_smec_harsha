//
// Created by harsha on 2019-05-27.
//

#include "controller.h"

cell *** init_app() {
    cell *** state = create_singleton_state();
    //do something else
    return state;
}

int run_app(cell *** state) {
    int run = 1;
    while(run != -1) {
        run = execute_command(state);
    }
    return -1;
}

int command_map(char *command) {
    if (compareStringsCaseInsensitive(command, "set")) {
        return 1;
    } else if (compareStringsCaseInsensitive(command, "get")) {
        return 2;
    } else if (compareStringsCaseInsensitive(command, "print")) {
        return 3;
    } else if (compareStringsCaseInsensitive(command, "import")) {
        return 4;
    } else if (compareStringsCaseInsensitive(command, "export")) {
        return 5;
    } else if (compareStringsCaseInsensitive(command, "exit")) {
        return 6;
    } else {
        return -1;
    }
}

char ** parse_command(char * input) {
    char * inp = trim(input);

    char * command = create_string(10);
    int i, k = 0;
    for (i = 0; inp[i] != ' ' && inp[i]; i++) {
        command[i] = inp[i];
    }
    command[i] = 0;

    char * args = create_string(100);
    for (; inp[i]; i++) {
        if (inp[i] != ' ') {
            args[k++] = inp[i];
        }
    }
    args[k] = 0;
    char ** parsed = (char **)malloc(sizeof(char *)*2);
    parsed[0] = command;
    parsed[1] = args;
    return parsed;
}

int execute_command(cell *** state) {
    char * input = create_string(1024);
    printf("\n> ");
    gets(input);
    char * answer;
    char ** parsed = parse_command(input);
    int command = command_map(parsed[0]);
    switch(command) {
        case 1:
            set(state, parsed[1]);
            break;
        case 2:
            answer = get(state, parsed[1]);
            printf("%s\n", answer); //TODO SHOW EXPRESSION
            break;
        case 3:
            print(state);
            break;
        case 4:
            save_data_to_state(state, get_data_from_file(parsed[1]));
//            state = get_data_from_file(parsed[1]);
            break;
        case 5:
//            write_data_to_file(parsed[1], state);
            break;
        case 6:
            return -1;
        default:
            print_command_not_found_exception();
            break;
    }
    return 1;
}

void kill_app(cell *** state) {
    //do something
}