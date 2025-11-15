#include "hash_map.h"
#include <stdio.h>
#include <string.h>

HashMap *hash_map_create(size_t key_size, size_t element_size, size_t capacity,
                         HashFunction hash_function,
                         KeyComparator key_comparator,
                         ProbeFunction probe_function) {
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  map->size = 0;
  map->capacity = capacity;
  map->element_size = element_size;
  map->key_size = key_size;
  map->hash_function = hash_function;
  map->key_comparator = key_comparator;
  map->probe_function = probe_function;
  map->keys = malloc(capacity * key_size);
  map->values = malloc(capacity * element_size);
  map->state = malloc(capacity * sizeof(unsigned char));

  return map;
}

void hash_map_free(HashMap *map) {
  free(map->keys);
  free(map->values);
  free(map->state);
  free(map);
}

size_t probe(HashMap *map, const void *key, size_t i) {
  return (map->hash_function(key) + map->probe_function(i)) % map->capacity;
}

size_t find_slot(HashMap *map, const void *key, int *found) {
  for (size_t i = 0; i < map->capacity; i++) {
    size_t index = probe(map, key, i);
    if (map->state[index] == 0) {
      *found = 0;
      return index; // Empty slot
    } else if (map->state[index] == 1 &&
               map->key_comparator((char *)map->keys + index * map->key_size,
                                   key) == 0) {
      *found = 1;
      return index; // Key found
    }
  }
  *found = 0;
  return map->capacity; // Not found
}

int hash_map_insert(HashMap *map, const void *key, const void *value) {
  if (map->size >= map->capacity) {
    return -1; // Map is full
  }

  int found = 0;
  size_t index = find_slot(map, key, &found);

  if (found == 1) {
    memcpy((char *)map->values + index * map->element_size, value,
           map->element_size);
    return 0;
  }

  memcpy((char *)map->keys + index * map->key_size, key, map->key_size);
  memcpy((char *)map->values + index * map->element_size, value,
         map->element_size);
  map->state[index] = 1; // Mark as occupied
  map->size++;

  return 0;
}

int hash_map_get(HashMap *map, const void *key, void *out_value) {
  int found = 0;
  size_t index = find_slot(map, key, &found);

  if (found != 1) {
    return -1; // Not found
  }

  memcpy(out_value, (char *)map->values + index * map->element_size,
         map->element_size);

  return 0;
}

int hash_map_remove(HashMap *map, const void *key) {
  int found = 0;
  size_t index = find_slot(map, key, &found);

  if (found == 1) {
    map->state[index] = 2; // Mark as deleted
    map->size--;
    return 0;
  }

  return -1; // Not found
}

size_t hash_map_size(HashMap *map) { return map->size; }
