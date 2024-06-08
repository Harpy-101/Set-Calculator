#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include "set.h"
#include "panic.h"

SET set_list[6];/*An array to hold all the known sets in this program */

char *set_names1[] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};

/**
 * @brief Builds the "set_list" that would be used for data storage and manipulation in the program".
 * 
 * @param set_list The array that will hold all the sets permitted for this program.
 * @param set_names The array that holds all the permitted set names to be used for the "name" value for each set.
 */
void build_set_list(SET *set_list, char **set_names) {
    int i, j;
    for (i = 0; i < MAX_SETS; i++) {
        strcpy(set_list[i].name, set_names[i]);
        for (j = 0; j < 16; j++) {
            set_list[i].val[j] = 0; // Initialize all bits to 0
        }
    }
}

/**
 * @brief A function that would be used in main to initiate the  "build_set_list()".
 * 
 */
void build() {
    build_set_list(set_list, set_names1);
}

/**
 * @brief This function adds the num into set. 
 * 
 * @param set The set in question. 
 * @param num The num in question.
 */
void add_val(SET *set, int num) {
    int index = num / 8;
    int bit_index = num % 8;
    set->val[index] |= (1 << bit_index);
}

/**
 * @brief This function fetches num from set
 * 
 * @param set The set in question. 
 * @param num The num in question.
 * @return int 
 */
int get_val(SET *set, int num) {
    int index = num / 8;
    int bit_index = num % 8;
    return (set->val[index] & (1 << bit_index)) != 0;
}

/**
 * @brief The function assigns values for a given set. 
 * 
 * @param set The set that would get assigned values. 
 * @param input The array of chars holding the values that will get assigned to the set. 
 */
void read_set2(SET *set, char *input) {
    int arr_val[1024] = {[0 ... 1023] = MAX_VAL};
    int status;
    status = id_illegal_chars(input, arr_val);
    if (status == 0) { 
        return;
    }
    change_set(set, arr_val);
}

/**
 * @brief The function hunts for illegal values potentially hiding in the input.
 * 
 * @param input The array of values that will be scanned  
 * @param arr_val The array of values that will hold the values deemed acceptable.
 * @return int Can either return 0 (failure in one of the tests) or 1 (no illegal cases were found).
 */
int id_illegal_chars(char *input, int *arr_val) {
    int i = 0, j = 0, k = 0, val;
    char buffer[10] = {0}; // buffer to hold the current number as a string

    while (input[i] != '\0') {
        if ((isdigit(input[i]) || input[i] == '-')) {
            buffer[k++] = input[i]; // collect digits and possible minus sign
        } else if (input[i] == ',' || isspace(input[i])) {
            if (k > 0) {
                buffer[k] = '\0'; // Null-terminate the buffer
                val = atoi(buffer); // Convert to integer
                if (val > SET_MAX_VAL || (val < SET_LOWEST_VAL && val != TERMINATION_VAL)) {
                    illegal_value_out_of_range();
                    return 0;
                }
                if (id_duplicates_int(arr_val, j, val)) {
                    arr_val[j++] = val;
                }
                k = 0; // Reset buffer index for the next number
            }
            if (input[i] == ',' && input[i - 1] == ',') {
                consecutive_commas();
                return 0; // Error: consecutive commas
            }
        } else {
            illegal_value_not_a_number();
            return 0; // Error: illegal character found
        }
        i++;
    }
    
    if (k > 0) {
        buffer[k] = '\0';
        val = atoi(buffer);
        if (val != TERMINATION_VAL) {
            missing_set_terminator();
            return 0; // Error: missing -1
        }
        if (id_duplicates_int(arr_val, j, val)) {
            arr_val[j++] = val;
        }
    }
    
    arr_val[j] = MAX_VAL; // Add terminator
    qsort(arr_val, j, sizeof(int), cp_ascending);

    return 1; // Successfully processed the input
}

/**
 * @brief This function assigns the values stored in "arr" to the set.
 * 
 * @param SET The set in question.
 * @param arr The arr in question.
 */
void change_set(SET *set, int *arr) {
    reset_set(set);
    for (int i = 0; i < 128 && arr[i] != MAX_VAL; i++) {
        add_val(set, arr[i]);
    }
}

/**
 * @brief The function iterates through the values stored in "arr" to determine whether the value "val" is present inside it.
 * 
 * @param arr The array holding all the values that have been processed in the parent function thus far.
 * @param len The amount of values in “arr”. 
 * @param val The value that is being compared.
 * @return int If “0” then the value was found (i.e, it's a duplicate) and if “1” than the value is new.
 */
int id_duplicates_int(int *arr, int len, int val) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == val) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief This function is used for the "qsort" function
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cp_ascending(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * @brief This function prints the value of the given set.
 * 
 * @param SET The set in question.
 */
void print_set(SET *set) {
    int count = 0;
    for (int i = 0; i < 128; i++) {
        if (get_val(set, i)) {
            if (count > 0) {
                printf(", ");
            }
            printf("%d", i);
            count++;
            if (count % 16 == 0) {
                printf("\n");
            }
        }
    }
    if (count == 0) {
        printf("The set is empty\n");
    } else {
        printf("\n");
    }
}

/**
 * @brief This function unionizezed the SET1 and SET2 and after doing so, it stores the outcome of siad union in SET3 
 * 
 * @param SET1 First parameter.
 * @param SET2 Second paremeter.
 * @param SET3 Result paremeter.
 */
void union_set(SET *SET1, SET *SET2, SET *SET3) {
    int arr[128] = {[0 ... 127] = MAX_VAL};
    int j = 0;
    for (int i = 0; i < 128; i++) {
        if (get_val(SET1, i) || get_val(SET2, i)) {
            arr[j++] =  i;
        }
    }
    reset_set(SET3);
    change_set(SET3, arr);
}

/**
 * @briefThis function finds the intersecting values between SETA and SETB. it then stores the result in SET3.
 * 
 * @param SET1 First parameter.
 * @param SET2 Second paremeter.
 * @param SET3 Result paremeter.

 */
void intersect_set(SET *SET1, SET *SET2, SET *SET3) {
    int arr[128] = {[0 ... 127] = MAX_VAL};
    int j = 0;
    for (int i = 0; i < 128; i++) {
        if (get_val(SET1, i) && get_val(SET2, i)) {
            arr[j++] = i;
        }
    }
    reset_set(SET3);
    change_set(SET3, arr);
}

/**
 * @brief This function zeros out the SET.
 * 
 * @param SET The set in question. 
 */
void reset_set(SET *set) {
    for (int i = 0; i < 16; i++) {
        set->val[i] = 0;
    }
}

/**
 * @briefThis function performs the subtraction between SET1 and SET2. It then stores the result in SET 3.  
 * 
 * @param SET1 First parameter.
 * @param SET2 Second paremeter.
 * @param SET3 Result paremeter.
 */
void sub_set(SET *SET1, SET *SET2, SET *SET3) {
    int arr[128] = {[0 ... 127] = MAX_VAL};
    int j = 0;
    for (int i = 0; i < 128; i++) {
        if (get_val(SET1, i) && !get_val(SET2, i)) {
            arr[j++] = i;
        }
    }
    reset_set(SET3);
    change_set(SET3, arr);
}
/*
int set_len(SET *set) {
    int count = 0;
    for (int i = 0; i < 128; i++) {
        if (get_set(set, i)) {
            count++;
        }
    }
    return count;
}
*/

/**
 * @briefThis function finds the symmetrical difference between SET1 and SET2. It then stores the result in SET3.
 * 
 * @param SET1 First parameter.
 * @param SET2 Second paremeter.
 * @param SET3 Result paremeter.
 */
void symdiff_set(SET *SET1, SET *SET2, SET *SET3) {
    int arr[128] = {[0 ... 127] = MAX_VAL};
    int j = 0;
    for (int i = 0; i < 128; i++) {
        if (get_val(SET1, i) != get_val(SET2, i)) {
            arr[j++] = i;
        }
    }
    reset_set(SET3);
    change_set(SET3, arr);
}

/*
int extract_set_vals(SET *set, int *arr) {
    int count = 0;
    for (int i = 0; i < 128; i++) {
        if (get_set(set, i)) {
            arr[count++] = i;
        }
    }
    return count;
}
*/

/**
 * @brief This function stops the program. 
 * 
 */
void stop() {
    exit(EXIT_FAILURE);
}



