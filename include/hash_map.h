#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdlib.h>

typedef size_t (*HashFunction)(const void *key);
typedef int (*KeyComparator)(const void *key1, const void *key2);

typedef struct {
  void *keys;
  void *values;
  size_t size;
  size_t capacity;
  size_t element_size;
  HashFunction hash_function;
  KeyComparator key_comparator;
  unsigned char *state; // 0 = empty, 1 = occupied, 2 = deleted
} HashMap;

HashMap *hash_map_create(size_t key_size, size_t value_size,
                         HashFunction hash_function,
                         KeyComparator key_comparator);

void hash_map_free(HashMap *map);

int *hash_map_insert(HashMap *map, const void *key, const void *value);
int *hash_map_get(HashMap *map, const void *key);
int *hash_map_remove(HashMap *map, const void *key);

#endif
