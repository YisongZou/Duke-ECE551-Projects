#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  uint64_t * ans = new uint64_t[257]();
  ans[256] = 1;
  std::ifstream ifs;
  ifs.open(fname, std::ifstream::in);
  if (ifs.fail()) {
    std::cerr << "Can't read file" << std::endl;
    exit(EXIT_FAILURE);
  }
  int c = 0;
  while ((c = ifs.get()) != EOF) {
    ans[c]++;
  }
  ifs.close();
  return ans;
  //WRITE ME!
}
