#include <stdio.h>
#include <stdlib.h>
int power_helper(int x, int y, int ans) {
  if (y <= 0) {
    return ans;
  }
  return power_helper(x, y - 1, ans * x);
}
unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  return power_helper(x, y, 1);
}
