#include "calculate.h"

Stack *init(Lexeme *node) {
  Stack *new_node = NULL;
  if (node) {
    new_node = calloc(1, sizeof(Stack));
    new_node->node = *node;
    new_node->next = NULL;
  }
  return new_node;
}

char peek_type(Stack *root) {
  char type = 0;
  if (root) type = root->node.type;
  return type;
}

double peek_value(Stack *root) {
  double value = 0;
  if (root) value = root->node.value;
  return value;
}

int peek_rang(char type) {
  int rang = 0;
  if (type == '-' || type == '+')
    rang = 1;
  else if (type == '/' || type == '*' || type == '%')
    rang = 2;
  else if (type == '^')
    rang = 3;
  else if (type == '~' || type == '#')
    rang = 4;
  else if (type == 's' || type == 'c' || type == 't' || type == 'S' ||
           type == 'C' || type == 'T' || type == 'L' || type == 'l' ||
           type == 'q') {
    rang = 5;
  }
  return rang;
}

void push(Stack **root, Lexeme *node) {
  if (node) {
    Stack *new_stack_node = init(node);
    new_stack_node->next = *root;
    *root = new_stack_node;
  }
}

void pop(Stack **root) {
  if (*root) {
    Stack *node = *root;
    *root = (*root)->next;
    free(node);
  }
}

void destroy(Stack **root) {
  if (*root) {
    Stack *remove = *root;
    while (remove) {
      *root = (*root)->next;
      free(remove);
      remove = *root;
    }
  }
}