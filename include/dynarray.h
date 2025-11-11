#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stdlib.h>

typedef struct {
  void *data;
  size_t size;
  size_t capacity;
  size_t element_size;
} DynArray;

DynArray *dynarray_create(size_t element_size);
void dynarray_free(DynArray *array);

int dynarray_push_back(DynArray *array, const void *element);
int dynarray_pop_back(DynArray *array);
void *dynarray_get(DynArray *array, size_t index);
size_t dynarray_size(DynArray *array);

#endif
