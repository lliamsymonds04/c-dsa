#include "dynarray.h"
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 4

DynArray *dynarray_create(size_t element_size) {
  DynArray *array = malloc(sizeof(DynArray));
  if (!array) return NULL;

  array->data = malloc(INITIAL_CAPACITY * element_size);
  if (!array->data) {
    free(array);
    return NULL;
  }

  array->size = 0;
  array->capacity = INITIAL_CAPACITY;
  array->element_size = element_size;
  return array;
}

void dynarray_free(DynArray *array) {
  if (array) {
    free(array->data);
    free(array);
  }
}

int dynarray_push_back(DynArray *array, const void *element) {
  // Check if resizing is needed
  if (array->size >= array->capacity) {
    size_t new_capacity = array->capacity * 2;
    void *new_data = realloc(array->data, new_capacity * array->element_size);
    if (!new_data) return -1; // Memory allocation failed

    array->data = new_data;
    array->capacity = new_capacity;
  }

  // Add the new element
  void *target = (char *)array->data + (array->size * array->element_size);
  memcpy(target, element, array->element_size);

  array->size++;
  return 1;
}

int dynarray_pop_back(DynArray *array) {
  if (array->size == 0) return -1; // Array is empty

  array->size--;
  return 1;
}

void *dynarray_get(DynArray *array, size_t index) {
  if (index >= array->size) return NULL; // Index out of bounds

  return (char *)array->data + (index * array->element_size);
}

size_t dynarray_size(DynArray *array) {
  return array->size;
}
