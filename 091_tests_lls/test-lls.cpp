#include <assert.h>

#include <cstdlib>

#include "il.h"
void testList(void) {
  IntList t1;
  IntList t2;
  IntList t4;
  IntList t5;
  assert(t5.getSize() == 0);
  t1.addFront(1);
  assert(t1[0] == 1);
  t1.addBack(2);
  t2.addFront(3);
  t1.remove(1);
  assert(t1[0] == 2);
  t1 = t2;
  assert(t1[0] == 3);
  IntList t3(t1);
  assert(t3[0] == 3);
  assert(t1.find(3) == 0);
  t4.addBack(9);
  t1[0] = t4[0];
  assert(t1[0] == 9);
  t1.~IntList();
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
