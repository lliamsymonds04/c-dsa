#include "linked_list.h"
#include <stdio.h>

void output_linked_list(LinkedList *list) {
  Node *current = list->head;
  printf("LinkedList (size=%zu): ", list->size);
  while (current) {
    printf("%d -> ", *(int *)current->value);
    current = current->next;
  }
  printf("NULL\n");
}

int test_linked_list(void) {
  printf("[TEST] linked_list...\n");
  LinkedList *list = linked_list_create(sizeof(int));

  // Test added at tail
  for (int i = 1; i <= 5; i++) {
    add_at_tail(list, &i);
  }

  add_at_head(list, &(int){0});

  output_linked_list(list);

  // remove tail
  remove_at_tail(list);

  output_linked_list(list);

  // Reverse list
  linked_list_reverse(list);

  output_linked_list(list);

  printf("Find node with value 3: ");
  Node *node_3 = find_node(list, &(int){3});
  if (node_3) {
    printf("Found node with value %d\n", *(int *)node_3->value);
  } else {
    printf("Node not found\n");
  }

  printf("Passed all linked list tests.\n");

  linked_list_free(list);

  return 1;
}
