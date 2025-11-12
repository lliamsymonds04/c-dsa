#include "stack.h"

#include <stdlib.h>
#include <string.h>

Stack *stack_create(size_t element_size) {
  Stack *stack = malloc(sizeof(Stack));
  if (!stack) return NULL;

  stack->array = dynarray_create(element_size);
  if (!stack->array) {
    free(stack);
    return NULL;
  }

  return stack;
}

void stack_free(Stack *stack) {
  if (stack) {
    dynarray_free(stack->array);
    free(stack);
  }
}

int stack_push(Stack *stack, const void *element) {
  if (!stack || !element) return -1;

  if (dynarray_push_back(stack->array, element) != 0) return -1;

  return 0;
}

int stack_pop(Stack *stack, void *out) {
  if (!stack) return -1;

  void *top_elem = stack_top(stack);
  memcpy(out, top_elem, stack->array->element_size);

  return dynarray_pop_back(stack->array);
}

void *stack_top(const Stack *stack) {
  if (!stack || stack_is_empty(stack)) return NULL;

  return dynarray_get(stack->array, dynarray_size(stack->array) - 1);
}

size_t stack_size(const Stack *stack) {
  if (!stack) return 0;

  return dynarray_size(stack->array);
}

int stack_is_empty(const Stack *stack) {
  if (!stack) return 1;

  return dynarray_size(stack->array) == 0;
}
