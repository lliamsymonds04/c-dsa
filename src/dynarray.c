#include "dynarray.h"
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 4

DynArray *dynarray_create(size_t element_size) {
  DynArray *array = malloc(sizeof(DynArray));
  if (!array)
    return NULL;

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
    if (!new_data)
      return -1; // Memory allocation failed

    array->data = new_data;
    array->capacity = new_capacity;
  }
  return 0;
}

int dynarray_push_back(DynArray *array, const void *element) {
  if (resize_if_needed(array) == -1)
    return -1;

  // Add the new element
  void *target = (char *)array->data + (array->size * array->element_size);
  memcpy(target, element, array->element_size);

  array->size++;
  return 0;
}

int dynarray_pop_back(DynArray *array) {
  if (array->size == 0)
    return -1; // Array is empty

  array->size--;
  return 0;
}

int dynarray_insert(DynArray *array, const void *element, size_t index) {
  if (index > array->size)
    return -1; // Index out of bounds

  if (resize_if_needed(array) == -1)
    return -1;

  // Insert the new element
  char *base = (char *)array->data;
  void *dest = base + (index * array->element_size);

  // move data to right to fit place new element
  memmove((char *)dest + array->element_size, dest,
          (array->size - index) * array->element_size);

  // Copy new element into the gap
  memcpy(dest, element, array->element_size);
  array->size++;

  return 0;
}

int dynarray_remove(DynArray *array, size_t index) {
  if (index >= array->size)
    return -1; // Index out of bounds

  // move data to left to fill the gap
  char *base = (char *)array->data;
  char *dest = base + index * array->element_size;
  char *src = base + (index + 1) * array->element_size;

  memmove(dest, src, (array->size - index - 1) * array->element_size);

  array->size--;

  return 0;
}

void *median_of_three(DynArray *array, Comparator comparator, size_t low,
                      size_t high) {
  char *base = (char *)array->data;

  size_t mid = low;
  void *lowPtr = base + (low * array->element_size);
  void *midPtr = base + (mid * array->element_size);
  void *highPtr = base + (high * array->element_size);

  if (comparator(lowPtr, midPtr) > 0) {
    if (comparator(lowPtr, highPtr) < 0) {
      return lowPtr;
    } else if (comparator(midPtr, highPtr) > 0) {
      return midPtr;
    } else {
      return highPtr;
    }
  } else {
    if (comparator(lowPtr, highPtr) > 0) {
      return lowPtr;
    } else if (comparator(midPtr, highPtr) < 0) {
      return midPtr;
    } else {
      return highPtr;
    }
  }
}

size_t partition(DynArray *array, Comparator comparator, size_t low,
                 size_t high) {
  char *base = (char *)array->data;
  void *pivot = median_of_three(array, comparator, low, high);
  size_t leftWall = low;

  void *temp = malloc(array->element_size);
  if (!temp) {
    // Handle memory allocation failure
    exit(EXIT_FAILURE);
  }

  for (size_t i = low + 1; i <= high; i++) {

    void *iPtr = base + (i * array->element_size);
    if (comparator(iPtr, pivot) < 0) {
      leftWall++;

      // Swap elements at i and leftWall
      void *leftWallPtr = base + (leftWall * array->element_size);
      memcpy(temp, leftWallPtr, array->element_size);
      memcpy(leftWallPtr, iPtr, array->element_size);
      memcpy(iPtr, temp, array->element_size);
    }
  }

  // swap pivot with leftWall
  void *leftWallPtr = base + (leftWall * array->element_size);
  void *pivotPtr = base + (low * array->element_size);

  memcpy(temp, leftWallPtr, array->element_size);
  memcpy(leftWallPtr, pivotPtr, array->element_size);
  memcpy(pivotPtr, temp, array->element_size);

  free(temp);
  return leftWall;
}

void quick_sort(DynArray *array, Comparator comparator, size_t low,
                size_t high) {
  if (low < high) {
    // Partitioning index
    size_t pivot_index = partition(array, comparator, low, high);
    if (pivot_index > 0) {
      quick_sort(array, comparator, low, pivot_index - 1);
    }
    quick_sort(array, comparator, pivot_index + 1, high);
  }
}

int dynarray_sort(DynArray *array, Comparator comparator) {
  if (!array || array->size <= 1)
    return 0; // Already sorted
  quick_sort(array, comparator, 0, array->size - 1);
  return 0;
}

void *dynarray_get(DynArray *array, size_t index) {
  if (index >= array->size)
    return NULL; // Index out of bounds

  return (char *)array->data + (index * array->element_size);
}

size_t dynarray_size(DynArray *array) { return array->size; }
