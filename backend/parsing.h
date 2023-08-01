#ifndef PARSING_H
#define PARSING_H

#include "stack.h"

int parse_expression(char* expression, double x, Stack** numbers,
                     Stack** operations);
int read_digit(char* expression, double x, Stack** numbers);
int read_mod(char* expression, int* position);
char handle_unary_sign(char type, char last_read);
int read_binary_operation(char type, char* last_read, Stack** numbers,
                          Stack** operations, int* i);
int read_brackets(char type, Stack** numbers, Stack** operations);
int read_function(char* expression, Stack** operations);

#endif  // PARSING_H