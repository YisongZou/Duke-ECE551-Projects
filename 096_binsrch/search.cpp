#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int ans = f->invoke((high + low) / 2);
  if (low + 1 >= high) {
    return low;
  }
  else if (ans == 0) {
    return (high + low) / 2;
  }
  else if (ans > 0) {
    high = (high + low) / 2;
    return binarySearchForZero(f, low, high);
  }
  else if (ans < 0) {
    low = (high + low) / 2;
    return binarySearchForZero(f, low, high);
  }
  return 0;
}
