#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList *linked_list_create(size_t element_size) {
  LinkedList *list = malloc(sizeof(LinkedList));
  if (!list)
    return NULL;

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  list->element_size = element_size;
  return list;
}

void linked_list_free(LinkedList *list) {
  if (!list)
    return;

  Node *current = list->head;
  while (current) {
    Node *next = current->next;
    free(current->value);
    free(current);
    current = next;
  }
  free(list);
}

Node *create_node(const void *value, size_t element_size) {
  Node *new_node = malloc(sizeof(Node));
  if (!new_node)
    return NULL;

  new_node->value = malloc(element_size);
  if (!new_node->value) {
    free(new_node);
    return NULL;
  }
  memcpy(new_node->value, value, element_size);
  new_node->next = NULL;
  return new_node;
}

int add_at_head(LinkedList *list, const void *value) {
  if (!list)
    return -1;

  Node *new_node = create_node(value, list->element_size);
  if (!new_node)
    return -1;

  new_node->next = list->head;
  list->head = new_node;

  // Assign tail if list is empty
  if (list->size == 0)
    list->tail = new_node;

  list->size++;
  return 0;
}

int add_at_tail(LinkedList *list, const void *value) {
  if (!list)
    return -1;

  Node *new_node = create_node(value, list->element_size);
  if (!new_node)
    return -1;

  if (list->tail)
    list->tail->next = new_node;
  list->tail = new_node;

  // Assign head if list is empty
  if (list->size == 0)
    list->head = new_node;

  list->size++;
  return 0;
}

int remove_at_head(LinkedList *list) {
  if (!list || !list->head)
    return -1;

  Node *old_head = list->head;
  list->head = old_head->next;

  if (list->head == NULL)
    list->tail = NULL;

  free(old_head->value);
  free(old_head);

  list->size--;

  return 0;
}

int remove_at_tail(LinkedList *list) {
  if (!list || !list->tail)
    return -1;

  if (list->head == list->tail) {
    free(list->head->value);
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
  } else {
    Node *current = list->head;

    // Find the node before the tail
    while (current->next != list->tail) {
      current = current->next;
    }
    free(list->tail->value);
    free(list->tail);
    current->next = NULL;
    list->tail = current;
  }

  list->size--;

  return 0;
}

Node *find_node(LinkedList *list, const void *value) {
  if (!list)
    return NULL;

  Node *current = list->head;
  while (current) {
    if (memcmp(current->value, value, list->element_size) == 0)
      return current;
    current = current->next;
  }
  return NULL;
}

int is_empty(LinkedList *list) { return list->size == 0; }

size_t linked_list_size(LinkedList *list) {
  if (!list)
    return 0;
  return list->size;
}

void *linked_list_get(LinkedList *list, size_t index) {
  if (!list || index >= list->size)
    return NULL;

  Node *current = list->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }
  return current->value;
}

int linked_list_reverse(LinkedList *list) {
  if (!list || list->size <= 1)
    return 0;

  Node *prev = NULL;
  Node *next = NULL;
  Node *curr = list->head;

  list->tail = list->head;

  while (curr) {
    // save next node
    next = curr->next;

    // point curr's next to prev
    curr->next = prev;

    // update pointers
    prev = curr;
    curr = next;
  }

  list->head = prev;

  return 1;
}
