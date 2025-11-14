#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct Node {
  void *value;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  size_t size;
  size_t element_size;
} LinkedList;

LinkedList *linked_list_create(size_t element_size);
void linked_list_free(LinkedList *list);

int add_at_head(LinkedList *list, const void *value);
int add_at_tail(LinkedList *list, const void *value);
int remove_at_head(LinkedList *list);
int remove_at_tail(LinkedList *list);
Node *find_node(LinkedList *list, const void *value);
int is_empty(LinkedList *list);
size_t linked_list_size(LinkedList *list);
void *linked_list_get(LinkedList *list, size_t index);
int linked_list_reverse(LinkedList *list);

#endif
