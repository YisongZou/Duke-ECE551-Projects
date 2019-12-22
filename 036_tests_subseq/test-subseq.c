#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);
void testmax(int array[], size_t n, size_t m) {
  if (maxSeq(array, m) != n) {
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  int array1[7] = {-3, 2, 3, 4, 3, 2, 1};
  int array2[7] = {7, 6, 5, 4, 3, 2, 1};
  int array3[7] = {0, 0, 0, 0, 0, 0, 0};
  int array4[7] = {1, 3, 0, 4, 5, 6};
  int array5[0] = {};
  int array6[7] = {-6, -5, -4, -6, -5, -4, -3};
  testmax(array1, 4, 7);
  testmax(array2, 1, 7);
  testmax(array3, 1, 7);
  testmax(array4, 4, 7);
  testmax(array5, 0, 0);
  testmax(array6, 4, 7);
  return EXIT_SUCCESS;
}
