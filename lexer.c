#include "lexer.h"

/* This is an array to store all of the valid commands. */
command command_list[MAX_NUM_COMMANDS];

/* This is an array to store all of the knowen command names. */
char *command_arr[] = {
    "read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set", "stop"
};

/*This array holds the amount of permitted arguments for every known command. */
int num_args_arr[] = {1, 1, 3, 3, 3, 3, 0};

char *set_names[] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};

/**
 * @brief This function takes the command names and amount of arguments and combines them into an array of commands structs to be used throughout the program. 
 * 
 * @param cmd_list The array of comads to populate. 
 * @param command_arr The names of each knowen command.
 * @param num_args_arrNumber of allowed arguments for each command.
 * @param command_numThe maximum amount of known commands for this program. 
 */
void build_command_list(command *cmd_list, char **command_arr, int *num_args_arr, int command_num) {
    int i;
    for (i = 0; i < command_num; i++) {
        strncpy(cmd_list[i].name, command_arr[i], MAX_NAME_LEN - 1);
        cmd_list[i].name[MAX_NAME_LEN - 1] = '\0';
        cmd_list[i].num_args = num_args_arr[i];
    }
}

/**
 * @brief This function calls "build_command_list" from main.
 * 
 */
void setup() {
    build_command_list(command_list, command_arr, num_args_arr, MAX_NUM_COMMANDS);
}

/**
 * @brief This function takes the user input and compares it to the known commands in this program in order to find a match. 
 * 
 * @param command_list the list of known commands.
 * @param input The user's input.
 * @param marker A marker to indicate the last index worked on in the user's input to be used (if necessary) in the next functions.
 * @return intReturns "i" to mark the index in of the command in the "command_list" if a valid command was identified.
 * A "-1" if no command was identified. 
 * And a "-2" if an illegal comma was identified.
 */
int id_func(command *command_list, char *input, char **marker) {
    int i;
    for (i = 0; i < MAX_NUM_COMMANDS; i++) {
        char *res = strstr(input, command_list[i].name);
        if (res != NULL) {
            int name_len = strlen(command_list[i].name);
            if (res == input || isspace((unsigned char)*(res - 1))) {
                if (*(res + name_len) == '\0' || isspace((unsigned char)*(res + name_len))) {
                    *marker = res + name_len;
                    return i;
                }
                else {
                    return -2;
                }
            }
        }
    }
    return -1;
}

/**
 * @brief This function calls the function the user requested if it was legal.
 * 
 * @param input The user's input. 
 * @param set_list The rray of all known sets.
 */
void exe_command_2 (char *input, SET *set_list) {
    int func_num;
    int num_args;
    char *marker = NULL;
    int id_comma;
    SET *set_ptr[MAX_SET_PTR];

    /* id the function the user requestd */
    func_num = id_func(command_list, input, &marker);
    if (func_num < 0) {
        if (func_num == -1) {
            wrond_command_name();
        }
        if (func_num == -2) {
            illegal_comma();
        }
        return;
    }

    /*printf("working with func number: %d\n", func_num); */

    /* id the parameters */
    num_args = id_args_2(input, set_list, set_ptr, &marker);
    if (num_args == -1 && func_num != STOP_CASE) {
        wrong_set_name();
        return;
    }
    else if (num_args != command_list[func_num].num_args && func_num != STOP_CASE) {
        if (num_args < command_list[func_num].num_args) {
            missing_parameter();
        }
        else {
            too_many_perameters();
        }
        return;
    }

    if (func_num != 0 ) {
        int status = id_irreleven_chars(marker);
        if (status != 0 ) {
            irrelevent_chars();
            return;
        }
    }
    if (func_num == 0) {
        id_comma = id_missing_comma(marker);
        if (id_comma != 1) {
            missing_comma();
            return;
        }
    }

    /*
    printf("Executing %s with arguments:", command_list[func_num].name);
    for (i = 0; i < num_args; i++) {
        printf(" %s", set_ptr[i]->name);
    }
    */
    printf("\n");

    if (strcmp(command_list[func_num].name, "read_set") == 0) {
        read_set2(set_ptr[0], marker);
    }
    else if (strcmp(command_list[func_num].name, "print_set") == 0) {
        print_set(set_ptr[0]);
    }
    else if (strcmp(command_list[func_num].name, "union_set") == 0) {
        union_set(set_ptr[0], set_ptr[1], set_ptr[2]);
    }
    else if (strcmp(command_list[func_num].name, "intersect_set") == 0) {
        intersect_set(set_ptr[0], set_ptr[1], set_ptr[2]);
    }
    else if (strcmp(command_list[func_num].name, "sub_set") == 0) {
        sub_set(set_ptr[0], set_ptr[1], set_ptr[2]);
    }
    else if (strcmp(command_list[func_num].name, "symdiff_set") == 0) {
        symdiff_set(set_ptr[0], set_ptr[1], set_ptr[2]);
    }
    else if (strcmp(command_list[func_num].name, "stop") == 0) {
        stop();
    }
}

/**
 * @briefThis function identifies the parameters the user wants to use the command with. It also checks how many parameters were entered and if they are in fact legal.  
 * 
 * @param input The user's input. 
 * @param set_list The array of all known sets.
 * @param set_ptr An array to store all the sets the user wants to operate on with the current command called.
 * @param marker A marker to indicate the last index worked on in the user's input to be used (if necessary) in the next functions. 
 * @return int The amount of commands, or "-1" if a wrong set was identified.
 */
int id_args_2(char *input, SET *set_list, SET **set_ptr, char **marker) {
    int args_num = 0, i;
    char *command_end = strchr(input, ' ');
    char *start;
    char *end;
    char temp;
    if (!command_end) {
        return 0;
    }

    command_end++;

    start = command_end;

    while ((end = strpbrk(start, ",\n")) != NULL || *start != '\0') { /* the old accepted values were ",\n'"*/
        if (end == NULL) {
            end = start + strlen(start);
        }

        while (isspace((unsigned char) *start)) {
            start++;
        }

        /* Check if the current character is a digit */
        if (isdigit((unsigned char) *start) || *start == '-') {
            break; /* Stop scanning for arguments if a number is found */
        }

        while (isdigit((unsigned char) *(end-1))) {
            end--;
        }
        while (end > start && isspace((unsigned char) *(end - 1))) { 
            end--;
        }

        temp = *end;
        *end = '\0';

        for (i = 0; i < MAX_NUM_COMMANDS; i++) {
            if (i == 6) {
                if (start == end) {
                    break;
                }
                return -1; /* could'nt id a set */
            }
            if (strcmp(start, set_list[i].name) == 0) {
                set_ptr[args_num++] = &set_list[i];
                *marker = end; 
                break;
            }
        }

        *end = temp;
        if (*end == '\0') {
            break;
        }
        start = end + 1;
    }
    return args_num;
}

/**
 * @brief If the function called is "read_set" it is necessary to check if a comma is placed after the command call this function does that.
 * 
 * @param input The user's input.
 * @return int "1" if a comma was found, and "0" if no comma was found.
 */
int id_missing_comma(char *input) {
    int i = 0;

    while (input[i] != ',') {
        if (input[i] == ' ') {
            i++;
            continue;
        }
        else {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief This function looks for irrelevant characters after the command.
 * 
 * @param input The user's input.
 * @return int "1" if such chars were detected else "0".
 */
int id_irreleven_chars(char *input) {
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ' || input[i] != '\n' || input[i] != EOF) {
            return 1;
        }
    }
    return 0;
}
