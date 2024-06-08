#ifndef SET_H
#define SET_H  
#include <complex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAL 255
#define MAX_SET_NAME 5
#define MAX_SETS 6
#define SET_MAX_VAL 127
#define SET_LOWEST_VAL 0
#define TERMINATION_VAL -1

typedef struct{
    char name [MAX_SET_NAME];
    uint8_t val[16];
} SET;

typedef uint8_t set[16];
extern SET set_list[6];

int cp_ascending(const void *a, const void *b);
int id_duplicates_int(int *arr, int len, int val);
int id_duplicates_set(set arr, int len, uint8_t val);  
unsigned int my_add(unsigned int a, unsigned int b);
/*void change_set(set SET, int *arr); */
/*void read_set(set SET);*/
void print_arr(uint8_t arr[]);
void clear_input_buffer();
void print_set(SET *SET);
void union_set(SET *SET1, SET *SET2, SET *SET3); 
void reset_set(SET *SET); 
void intersect_set(SET *SET1, SET *SET2, SET *SET3);
int set_len(SET *SET); 
void sub_set(SET *SET1, SET *SET2, SET *SET3); 
int extract_set_vals(SET *SET, int *arr); 
void symdiff_set(SET *SET1, SET *SET2, SET *SET3);
void stop();
void build();
void read_set2(SET *set, char *input); 
int id_illegal_chars(char *input, int *arr_val);
int id_num(char *input, int count); 
void change_set(SET *SET, int *arr);
void add_val(SET *set, int num);
int get_val(SET *set, int num); 



#endif