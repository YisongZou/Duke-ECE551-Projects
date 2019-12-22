// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>
int seq1(int x) {
  int y = 4 * x - 3;
  return y;
}
void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
  }
  else {
    for (int x = low; x < high; x++) {
      int y = 4 * x - 3;
      if ((x >= low) && (x < high - 1)) {
        printf("%d, ", y);
      }
      else {
        if (x == high - 1)
          printf("%d\n", y);
      }
    }
  }
}

int main(void) {
  int y = seq1(0);
  int x = 0;
  printf("seq1(%d) = %d\n", x, y);
  y = seq1(3);
  x = 3;
  printf("seq1(%d) = %d\n", x, y);
  y = seq1(-3);
  x = -3;
  printf("seq1(%d) = %d\n", x, y);
  y = seq1(999);
  x = 999;
  printf("seq1(%d) = %d\n", x, y);
  printf("printSeq1Range(%d, %d)\n", 0, 4);
  printSeq1Range(0, 4);
  printf("printSeq1Range(%d, %d)\n", -2, 6);
  printSeq1Range(-2, 6);
  printf("printSeq1Range(%d, %d)\n", 0, 0);
  printSeq1Range(0, 0);
  printf("printSeq1Range(%d, %d)\n", 7, 3);
  printSeq1Range(7, 3);
  return 0;
}
