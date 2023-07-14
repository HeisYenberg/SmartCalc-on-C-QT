#include "calculate.h"

int parse_expression(char *expression, double x, Stack **numbers,
                     Stack **operations) {
  int status = OK;
  char last_read = 0;
  int expression_length = (int)strlen(expression);
  for (int i = 0; i < expression_length && !status; i++) {
    if (isspace(expression[i])) {
      continue;
    } else if (strchr("acstl", expression[i])) {
      last_read = expression[i];
      int read = read_function(expression + i, operations);
      if (read > 0)
        i += read;
      else
        status = INCORRECT_EXPRESSION;
    } else if (isdigit(expression[i]) || expression[i] == 'x') {
      if (isdigit(last_read) || last_read == 'x') status = INCORRECT_EXPRESSION;
      i += read_digit(expression + i, x, numbers);
      last_read = expression[i];
    } else if (expression[i] == 'm') {
      status = read_mod(expression + i, &i);
    } else if (strchr("+-*%/^", expression[i])) {
      expression[i] = handle_unary_sign(expression[i], last_read);
      status = read_binary_operation(expression[i], &last_read, numbers,
                                     operations, &i);
    } else if (expression[i] == '(' || expression[i] == ')') {
      last_read = expression[i];
      status = read_brackets(expression[i], numbers, operations);
    } else {
      status = INCORRECT_EXPRESSION;
    }
  }
  return status;
}

char handle_unary_sign(char type, char last_read) {
  if (!isdigit(last_read) && last_read != 'x' && last_read != ')' &&
      (type == '-' || type == '+')) {
    if (type == '+')
      type = '#';
    else
      type = '~';
  }
  return type;
}

int read_mod(char *expression, int *possition) {
  int status = INCORRECT_EXPRESSION;
  if (!strncmp(expression, "mod", 3)) {
    (*possition)++;
    expression[2] = '%';
    status = OK;
  }
  return status;
}

int read_digit(char *expression, double x, Stack **numbers) {
  int read = 0;
  double node_double = x;
  if (expression[0] != 'x') {
    char *end = NULL;
    node_double = strtod(expression, &end);
    read = (int)(end - expression - 1);
  }
  Lexeme number = {0, node_double};
  push(numbers, &number);
  return read;
}

int read_binary_operation(char type, char *last_read, Stack **numbers,
                          Stack **operations, int *i) {
  int status = OK;
  int previous_rang = peek_rang(peek_type(*operations));
  if (previous_rang && peek_rang(type) <= previous_rang) {
    status = calculate(numbers, operations);
    (*i)--;
  } else {
    *last_read = type;
    Lexeme operator= {type, 0};
    push(operations, &operator);
  }
  return status;
}

int read_brackets(char type, Stack **numbers, Stack **operations) {
  int status = OK;
  if (type == '(') {
    Lexeme operator= {type, 0};
    push(operations, &operator);
  } else {
    while (peek_type(*operations) != '(' && !status) {
      status = calculate(numbers, operations);
      if (!peek_type(*operations)) status = INCORRECT_EXPRESSION;
    }
    pop(operations);
  }
  return status;
}

int read_function(char *expression, Stack **operations) {
  int read = -1;
  char type = 0;
  if (!strncmp("asin(", expression, 5)) {
    read += 4;
    type = 'S';
  } else if (!strncmp("acos(", expression, 5)) {
    read += 4;
    type = 'C';
  } else if (!strncmp("atan(", expression, 5)) {
    read += 4;
    type = 'T';
  } else if (!strncmp("sin(", expression, 4)) {
    read += 3;
    type = 's';
  } else if (!strncmp("cos(", expression, 4)) {
    read += 3;
    type = 'c';
  } else if (!strncmp("tan(", expression, 4)) {
    read += 3;
    type = 't';
  } else if (!strncmp("log(", expression, 4)) {
    read += 3;
    type = 'L';
  } else if (!strncmp("ln(", expression, 3)) {
    read += 2;
    type = 'l';
  } else if (!strncmp("sqrt(", expression, 5)) {
    read += 4;
    type = 'q';
  }
  Lexeme operator= {type, 0};
  push(operations, &operator);
  return read;
}