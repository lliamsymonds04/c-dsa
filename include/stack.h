#ifndef STACK_H
#define STACK_H

#include "dynarray.h"
#include <stdlib.h>

typedef struct {
  DynArray *array;
} Stack;

Stack *stack_create(size_t element_size);
void stack_free(Stack *stack);
int stack_push(Stack *stack, const void *element);
int stack_pop(Stack *stack, void *out);
void *stack_top(const Stack *stack);
size_t stack_size(const Stack *stack);
int stack_is_empty(const Stack *stack);

#endif
