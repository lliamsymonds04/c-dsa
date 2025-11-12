#include <stdio.h>
#include <string.h>

void test_dynarray(void);

int main(int argc, char *argv[]) {
  int run_all = (argc == 1);
  const char *test_name = run_all ? NULL : argv[1];

  if (run_all || strcmp(test_name, "dynarray") == 0) {
    test_dynarray();
  }

  return 0;
}
