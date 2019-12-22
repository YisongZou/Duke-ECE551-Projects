#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  size_t o = 1;
  size_t m = 1;
  if (n == 0) {
    m = 0;
    return m;
  }
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      o++;
      if (o > m) {
        m = o;
      }
    }
    else if (array[i] >= array[i + 1]) {
      o = 1;
    }
  }
  return m;
}
