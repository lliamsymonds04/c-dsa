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

int resize_if_needed(DynArray *array) {
  if (array->size >= array->capacity) {
    size_t new_capacity = array->capacity * 2;
    void *new_data = realloc(array->data, new_capacity * array->element_size);
    if (!new_data) return -1; // Memory allocation failed

    array->data = new_data;
    array->capacity = new_capacity;
  }
  return 1;
}

int dynarray_push_back(DynArray *array, const void *element) {
  if (resize_if_needed(array) == -1) return -1;

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

int dynarray_insert(DynArray *array, const void *element, size_t index) {
  if (index > array->size) return -1; // Index out of bounds

  if (resize_if_needed(array) == -1) return -1;

  // Insert the new element
  char *base = (char *)array->data;
  void *dest = base + (index * array->element_size);

  // move data to right to fit place new element
  memmove((char *)dest + array->element_size, dest, (array->size - index) * array->element_size);

  // Copy new element into the gap
  memcpy(dest, element, array->element_size);
  array->size++;

  return 1;
}

int dynarray_remove(DynArray *array, size_t index) {
  if (index >= array->size) return -1; // Index out of bounds

  // move data to left to fill the gap
  char *base = (char *)array->data;
  char *dest = base + index * array->element_size;
  char *src = base + (index + 1) * array->element_size;

  memmove(dest, src, (array->size - index - 1) * array->element_size);

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
