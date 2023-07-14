#include "calculate.h"

int smart_calc(char *expression, double x, double *result) {
  Stack *numbers = NULL, *operations = NULL;
  int status = parse_expression(expression, x, &numbers, &operations);
  while (!status && peek_type(operations))
    status = calculate(&numbers, &operations);
  if (!status) {
    *result = peek_value(numbers);
    pop(&numbers);
    if (numbers) status = INCORRECT_EXPRESSION;
  } else if (status == CALCULATION_ERROR) {
    *result = NAN;
  }
  destroy(&numbers);
  destroy(&operations);
  return status;
}

int calculate(Stack **numbers, Stack **operations) {
  int status = INCORRECT_EXPRESSION;
  char type = peek_type(*operations);
  if (strchr("+-*/%^", type)) {
    status = binary_calculation(numbers, operations);
  } else if (strchr("~#sctSCTLlq", type)) {
    status = functions_calculation(numbers, operations);
  }
  return status;
}

int binary_calculation(Stack **numbers, Stack **operations) {
  int status = OK;
  char type = peek_type(*operations);
  double a = peek_value(*numbers);
  pop(numbers);
  if (!*numbers) {
    status = INCORRECT_EXPRESSION;
  } else {
    double b = peek_value(*numbers);
    pop(numbers);
    double c = 0;
    if (type == '-') {
      c = b - a;
    } else if (type == '+') {
      c = b + a;
    } else if (type == '*') {
      c = b * a;
    } else if (type == '/') {
      if (a)
        c = b / a;
      else
        status = DIVISION_BY_ZERO;
    } else if (type == '%') {
      if (a)
        c = fmod(b, a);
      else
        status = DIVISION_BY_ZERO;
    } else if (type == '^') {
      c = pow(b, a);
    }
    if (isnan(c))
      status = CALCULATION_ERROR;
    else {
      Lexeme result = {0, c};
      push(numbers, &result);
      pop(operations);
    }
  }
  return status;
}

int functions_calculation(Stack **numbers, Stack **operations) {
  int status = OK;
  char type = peek_type(*operations);
  if (!*numbers) {
    status = INCORRECT_EXPRESSION;
  } else {
    double a = peek_value(*numbers);
    pop(numbers);
    pop(operations);
    double c = 0;
    if (type == '#') {
      c = a;
    } else if (type == '~') {
      c = -a;
    } else if (type == 's') {
      c = sin(a);
    } else if (type == 'c') {
      c = cos(a);
    } else if (type == 't') {
      c = tan(a);
    } else if (type == 'S') {
      c = asin(a);
    } else if (type == 'C') {
      c = acos(a);
    } else if (type == 'T') {
      c = atan(a);
    } else if (type == 'L') {
      c = log10(a);
    } else if (type == 'l') {
      c = log(a);
    } else if (type == 'q') {
      c = sqrt(a);
    }
    if (isnan(c))
      status = CALCULATION_ERROR;
    else {
      Lexeme result = {0, c};
      push(numbers, &result);
    }
  }
  return status;
}