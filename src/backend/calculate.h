#ifndef CALCULATE_H
#define CALCULATE_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "banking_calculations.h"
#include "parsing.h"

enum calculation_error {
  OK,
  INCORRECT_EXPRESSION,
  CALCULATION_ERROR,
  DIVISION_BY_ZERO
};

int smart_calc(char* expression, double x, double* result);
int calculate(Stack** numbers, Stack** operations);
int binary_calculation(Stack** numbers, Stack** operations);
int functions_calculation(Stack** numbers, Stack** operations);

#endif  // CALCULATE_H