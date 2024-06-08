# Set Calculator Program
### Overview

This program performs various set operations on sets of integers. The supported operations include union, intersection, subtraction, and symmetric difference. The program reads sets and commands from standard input, processes them, and outputs the results.

### Features

  - Union: Combines two sets into one containing all unique elements from both sets.
  - Intersection: Creates a set containing only elements present in both sets.
  - Subtraction: Creates a set containing elements from the first set that are not in the second set.
  - Symmetric Difference: Creates a set containing elements that are in either of the sets but not in both.
  - Comprehensive Error Handling: Ensures robust and user-friendly operation.
  - Modular Code Structure: Code is organized into multiple files for readability and maintainability.

### File Structure

  - set.c: Contains the implementation of set operations.
  - lexer.c: Handles input parsing and command interpretation.
  - myset.c: Main program file that coordinates input/output and set operations.
  - panic.c: Handles error messages and memory allocation failures.
  - set.h: Header file defining the set structure and function prototypes.
  - lexer.h: Header file for the lexer functions.
  - panic.h: Header file for error handling functions.

### Installation

To compile and run this program, you will need a C compiler (like gcc) installed on your system. Follow these steps to compile the program:
```c
git clone https://github.com/Harpy_101/Set-Calculator.git
cd set_alculator
gcc -o set_alculator set.c lexer.c myset.c panic.c
```
### Usage

Run the compiled program and provide input through standard input:
```c
./set_calculator
```
The input should be provided in the following format:

  [command] [set1, set2, ... ] *(if calling for read_set you must place a comma after stating the set. after the comma you can start entering numbers)*.

### Example input:
```
read_set SETA, 45, 23, 6, 7, 4, 3, 75 ,45, 34, -1
print_set SETA
read_set SETB, 5, 4, 3, 2, 78, 45, 43, -1
print_set SETB
read_set SETC,100,105,101,103,104,-1
print_set SETC
read_set SETC,127,0,3,126,127,0,-1
print_set SETC
read_set SETC,-1
print_set SETC
read_set SETD, -1
print_set SETD
read_set SETC , 110 , 111, 112 , -1
print_set SETC
union_set SETA, SETB, SETD
print_set SETD
intersect_set SETA, SETB, SETE
print_set SETE
sub_set SETA, SETB, SETF
print_set SETF
symdiff_set SETA, SETB, SETF
print_set SETF
intersect_set SETA, SETC, SETD
print_set SETD
union_set SETB, SETB, SETE
print_set SETE
stop
```

### Error Handling

The program includes comprehensive error handling for invalid input, memory allocation failures, and other potential issues. Informative error messages are provided to guide the user.