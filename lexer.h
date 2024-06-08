#ifndef LEXER_H
#define LEXER_H

#define MAX_NAME_LEN 20
#define MAX_NUM_COMMANDS 7
#define BUFFER_SIZE 1024
#define STOP_CASE 6
#define MAX_SET_PTR 10

#include <stdint.h>
#include "set.h"
#include "panic.h"
#include <ctype.h>
#include <string.h>


typedef struct {
    char name [MAX_NAME_LEN];
    int num_args;
} command;



void setup();
void print_command_list(command *cmd_list, int command_num);
void print_commands();
int id_func(command *command_list, char *input, char **marker); 
void add_zero(command *cmd_list, int index);
void exe_command_2 (char *input, SET *set_list); 
int id_args_2(char *input, SET *set_list, SET **set_ptr, char **marker); 
int id_missing_comma(char *input);
int id_irreleven_chars(char *input); 
#endif