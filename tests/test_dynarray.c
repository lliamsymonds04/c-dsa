#include "dynarray.h"
#include <stdio.h>

int compare_ints(const void *a, const void *b) {
  int x = *(const int *)a;
  int y = *(const int *)b;

  return (x > y) - (x < y);
}

int test_dynarray() {
  printf("[TEST] dynarray...\n");
  DynArray *array = dynarray_create(sizeof(int));

  for (int i = 0; i < 10; i++) {
    dynarray_push_back(array, &i);
  }

  for (size_t i = 0; i < dynarray_size(array); i++) {
    int *value = (int *)dynarray_get(array, i);
    printf("%d ", *value);
  }

  // test insert
  int value = 99;
  int index = 5;
  dynarray_insert(array, &value, index);
  if (*(int *)dynarray_get(array, index) == value) {
    printf("\nInsert test passed\n");
  } else {
    printf("\nInsert test failed\n");
  }

  for (size_t i = 0; i < dynarray_size(array); i++) {
    int *value = (int *)dynarray_get(array, i);
    printf("%d ", *value);
  }

  printf("\n");

  // test remove
  int remove_index = 3;
  dynarray_remove(array, remove_index);
  for (size_t i = 0; i < dynarray_size(array); i++) {
    int *value = (int *)dynarray_get(array, i);
    printf("%d ", *value);
  }

  printf("\n");

  // test sort
  dynarray_sort(array, compare_ints);

  for (size_t i = 0; i < dynarray_size(array); i++) {
    int *value = (int *)dynarray_get(array, i);
    printf("%d ", *value);
  }

  printf("\n");

  dynarray_free(array);

  printf("[PASSED]\n\n");
  return 1;
}
