#ifndef STACK_H
#define STACK_H

typedef struct lexeme {
  char type;
  double value;
} Lexeme;

typedef struct stack {
  Lexeme node;
  struct stack* next;
} Stack;

Stack* init(Lexeme* node);
char peek_type(Stack* root);
double peek_value(Stack* root);
int peek_rang(char type);
void push(Stack** root, Lexeme* node);
void pop(Stack** root);
void destroy(Stack** root);

#endif  // STACK_H