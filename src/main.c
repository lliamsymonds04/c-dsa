#include "dynarray.h"
#include <stdio.h>

int main() {
  DynArray *array = dynarray_create(sizeof(int));

  for (int i = 0; i < 10; i++) {
    dynarray_push_back(array, &i);
  }

  for (size_t i = 0; i < dynarray_size(array); i++) {
    int *value = (int *)dynarray_get(array, i);
    printf("%d ", *value);
  }

  printf("\n");

  dynarray_free(array);
  return 0;
}
