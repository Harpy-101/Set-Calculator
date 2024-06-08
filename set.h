#ifndef SET_H
#define SET_H  
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "panic.h"
#include <ctype.h>

#define MAX_VAL 255
#define MAX_SET_NAME 5
#define MAX_SETS 6
#define ARR_VAL_LEN 128
#define SET_MAX_VAL 127
#define SET_LOWEST_VAL 0
#define TERMINATION_VAL -1
#define LAST_SET_ELEMENT 16
#define BUFFER_SIZE 1024
#define CHAR_BUFFER 10

typedef struct{
    char name [MAX_SET_NAME];
    uint8_t val[16];
} SET;

extern SET set_list[6];

int cp_ascending(const void *a, const void *b);
int id_duplicates_int(int *arr, int len, int val);
void print_set(SET *SET);
void union_set(SET *SET1, SET *SET2, SET *SET3); 
void reset_set(SET *SET); 
void intersect_set(SET *SET1, SET *SET2, SET *SET3);
void sub_set(SET *SET1, SET *SET2, SET *SET3); 
void symdiff_set(SET *SET1, SET *SET2, SET *SET3);
void stop();
void build();
void read_set2(SET *set, char *input); 
int id_illegal_chars(char *input, int *arr_val);
void change_set(SET *SET, int *arr);
void add_val(SET *set, int num);
int get_val(SET *set, int num); 

#endif