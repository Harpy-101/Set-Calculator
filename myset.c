#include <stdio.h>
#include "set.h"
#include "lexer.h"
#include "panic.h"


int main() {
    char *input = NULL;
    int count = 1;

    build(); 
    setup();

    while (1) {
        printf("========================= Run number: \x1B[32m%d\033[0m  =========================\n", count);
        printf("\x1b[35mEnter command!\033[0m \n");
        input = calloc(BUFFER_SIZE, sizeof(char));
        if (input == NULL) {
            memory_allocation_failure();
            stop();
        }
        
        if (fgets(input, BUFFER_SIZE, stdin) != NULL) {
            if (*input == '\n') {
                free(input);
                continue;
            }
            printf("Your input is: %s\n", input);
            input[strcspn(input, "\n")] = 0; /* Remove the trailing newline character */
            exe_command_2(input, set_list);
        } else {
            if (feof(stdin)) {
                no_explicit_stop_called();
                free(input);
                stop();
            }
            else {
            input_detection_falied();
            stop();
            }
        }

        count++;
        free(input);
    }

    printf("\n");
    

    return 0;
}

