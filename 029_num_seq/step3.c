// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>
int seq3(int x, int y) {
  int value;
  value = -3 * x + (x + 2) * y;
  return value;
}
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int n = 0;
  if ((xLow >= xHi) || (yLow >= yHi)) {
    return 0;
  }
  for (int i = xLow; i <= xHi - 1; i++) {
    for (int j = yLow; j <= yHi - 1; j++) {
      if ((seq3(i, j) % 2) == 0) {
        n++;
      }
    }
  }
  return n;
}
int main(void) {
  int value;
  value = seq3(-4, -5);
  printf("seq3(%d, %d) = %d\n", -4, -5, value);
  value = seq3(0, 0);
  printf("seq3(%d, %d) = %d\n", 0, 0, value);
  value = seq3(-1, -3);
  printf("seq3(%d, %d) = %d\n", -1, -3, value);
  value = seq3(5, -5);
  printf("seq3(%d, %d) = %d\n", 5, -5, value);
  value = seq3(10, 10);
  printf("seq3(%d, %d) = %d\n", 10, 10, value);
  value = seq3(-50, -50);
  printf("seq3(%d, %d) = %d\n", -50, -50, value);
  value = countEvenInSeq3Range(0, 2, 0, 3);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, value);
  value = countEvenInSeq3Range(3, 5, -4, -5);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 3, 5, -4, -5, value);
  value = countEvenInSeq3Range(5, 3, -5, -4);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 5, 3, -5, -4, value);
  value = countEvenInSeq3Range(3, 5, -5, -3);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 3, 5, -5, -3, value);
  return 0;
}
