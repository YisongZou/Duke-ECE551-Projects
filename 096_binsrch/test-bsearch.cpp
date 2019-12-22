#include <math.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class MyFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg + 1; }
};

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int number;
  if (high > low) {
    number = log(high - low) / log(2) + 1;
  }
  else {
    number = 1;
  }
  CountedIntFn * count = new CountedIntFn(number, f, mesg);
  int ans = binarySearchForZero(count, low, high);
  if (ans != expected_ans) {
    std::cerr << "Wrong answer in " << mesg;
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  SinFunction sinf;
  check(&sinf, 0, 150000, 52359, "SinFunction");
  MyFunction myf;
  check(&myf, 0, 15, 0, "MyFunction");
  check(&myf, 2, 15, 2, "MyFunction");
  check(&myf, -5, -2, -3, "MyFunction");
  check(&myf, -5, -1, -2, "MyFunction");
  check(&myf, -10, 15, -1, "MyFunction");
  check(&myf, 9, 9, 9, "MyFunction");
  check(&myf, -999999, 1000000, -1, "MyFunction");

  return EXIT_SUCCESS;
}
