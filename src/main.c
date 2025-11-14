#include <stdio.h>
#include <string.h>

int test_dynarray(void);
int test_stack(void);
int test_linked_list(void);

int main(int argc, char *argv[]) {
  int run_all = (argc == 1);
  const char *test_name = run_all ? NULL : argv[1];

  int passed = 0;
  int total_tests = 0;

  if (run_all || strcmp(test_name, "dynarray") == 0) {
    passed += test_dynarray();
    total_tests++;
  }

  if (run_all || strcmp(test_name, "stack") == 0) {
    passed += test_stack();
    total_tests++;
  }

  if (run_all || strcmp(test_name, "linked_list") == 0) {
    passed += test_linked_list();
    total_tests++;
  }

  printf("\n [OVERALL] Passed %d out of %d tests.\n", passed, total_tests);

  return 0;
}
