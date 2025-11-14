#include "stack.h"
#include <stdio.h>

int test_stack() {
  printf("[TEST] stack...\n");
  Stack *stack = stack_create(sizeof(int));

  for (int i = 0; i < 10; i++) {
    int val = i;
    stack_push(stack, &val);
  }

  // test popping
  int value;
  for (int i = 0; i < 10; i++) {
    if (stack_pop(stack, &value) == 0) {
      printf("Popped: %d\n", value);
    } else {
      printf("Failed to pop from stack\n");
      exit(EXIT_FAILURE);
    }
  }

  stack_free(stack);
  printf("Stack test passed\n\n");

  return 0;
}
