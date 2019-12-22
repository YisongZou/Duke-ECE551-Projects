// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>
int seq2(int x) {
  int y;
  if ((x > 0) && ((x % 4) == 2)) {
    y = 2 * x;
  }
  else {
    if ((x < 0) && (((-x) % (-4)) == 2)) {
      y = 2 * x;
    }
    else {
      y = x * (x + 3) + 1;
    }
  }
  return y;
}
int sumSeq2(int low, int high) {
  int s = 0;
  if (low >= high) {
    return 0;
  }
  for (int i = low; i <= high - 1; i++) {
    s += seq2(i);
  }
  return s;
}
int main(void) {
  int y = seq2(2);
  printf("seq2(%d) = %d\n", 2, y);
  y = seq2(12);
  printf("seq2(%d) = %d\n", 12, y);
  y = seq2(13);
  printf("seq2(%d) = %d\n", 13, y);
  y = seq2(-4);
  printf("seq2(%d) = %d\n", -4, y);
  y = seq2(-2);
  printf("seq2(%d) = %d\n", -2, y);
  y = seq2(-6);
  printf("seq2(%d) = %d\n", -6, y);
  y = sumSeq2(0, 2);
  printf("sumSeq2(%d, %d) = %d\n", 0, 2, y);
  y = sumSeq2(3, 6);
  printf("sumSeq2(%d, %d) = %d\n", 3, 6, y);
  y = sumSeq2(9, 7);
  printf("sumSeq2(%d, %d) = %d\n", 9, 7, y);
  y = sumSeq2(9, 9);
  printf("sumSeq2(%d, %d) = %d\n", 9, 9, y);
  y = sumSeq2(-4, -1);
  printf("sumSeq2(%d, %d) = %d\n", -4, -1, y);
  y = sumSeq2(-3, 2);
  printf("sumSeq2(%d, %d) = %d\n", -3, 2, y);
  return 0;
}
