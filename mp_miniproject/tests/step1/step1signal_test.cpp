#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>
//test terminate signal
int main(void) {
  raise(3);
}
