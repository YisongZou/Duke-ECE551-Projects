#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
void check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) == expected_ans) {
    printf("success\n");
  }
  else {
    printf("failure\n");
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  check(2, 2, 4);
  check(-1, 2, 1);
  check(-1, 1, -1);
  check(0, 0, 1);
  return EXIT_SUCCESS;
}
