#include "panic.h"

void wrong_set_name() {
    printf("\033[31mpanic!\033[0m the set in quesion does'nt exist.\n");
}

void wrond_command_name() {
    printf("\033[31mpanic!\033[0m could'nt identify the command in question.\n");
}

void illegal_value_out_of_range() {
    printf("\033[31mpanic!\033[0m one of the values enterd is out of the permited range.\n");
}

void missing_set_terminator() {
    printf("\033[31mpanic!\033[0m you forgot to add \"-1\" when entring values for this set.\n");
}

void illegal_value_not_a_number() {
    printf("\033[31mpanic!\033[0m one of the values entred isn't an integer.\n");
}

void missing_parameter() {
    printf("\033[31mpanic!\033[0m tou're missing a perameter.\n");
}

void irrelevent_chars() {
    printf("\033[31mpanic!\033[0m extraneous text detected after the end of the command.\n");
}

void consecutive_commas() {
    printf("\033[31mpanic!\033[0m you enterd consecutive commas.\n");
}

void missing_comma() {
    printf("\033[31mpanic!\033[0m looks like you are missing a comma.\n");
}

void illegal_comma() {
    printf("\033[31mpanic!\033[0m looks like you placed an illegal comma.\n");
}

void memory_allocation_failure() {
    printf("\033[31mpanic!\033[0m failure to allocate memory.\n");
}

void input_detection_falied() {
    printf("\033[31mpanic!\033[0m detected no input.\n");
}

void too_many_perameters() {
    printf("\033[31mpanic!\033[0m too many perameters.\n");
}

void no_explicit_stop_called() {
    printf("\033[31mpanic!\033[0m no explicit \"stop\" was detected. Closing the program.\n"); 
}