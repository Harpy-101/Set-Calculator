#ifndef PANIC_H
#define PANIC_H

#include <stdio.h>

void wrong_set_name();
void wrond_command_name();
void illegal_value_out_of_range();
void missing_set_terminator();
void illegal_value_not_a_number();
void missing_parameter();
void irrelevent_chars();
void consecutive_commas();
void missing_comma();
void illegal_comma();
void memory_allocation_failure(); 
void input_detection_falied();
void too_many_perameters();
void no_explicit_stop_called(); 

#endif