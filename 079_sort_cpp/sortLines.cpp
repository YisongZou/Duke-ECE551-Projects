#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
void makesort(std::istream & istr) {
  std ::string inputline;
  std::vector<std::string> inputlines;
  while (std::getline(istr, inputline)) {
    inputlines.push_back(inputline);
  }
  if (!istr && !istr.eof()) {
    std::cerr << "Cannot read file" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::sort(inputlines.begin(), inputlines.end());
  for (std::vector<std::string>::const_iterator it = inputlines.begin();
       it != inputlines.end();
       ++it) {
    std::cout << *it << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 0) {
    std::cout << "Wrong number of command line argument";
    return EXIT_FAILURE;
  }
  if (argc == 1) {
    makesort(std::cin);
  }

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      std::ifstream ifstr(argv[i]);
      if (!ifstr) {
        std::cerr << "Cannot open" << argv[i] << std::endl;
        return EXIT_FAILURE;
      }
      makesort(ifstr);
    }
    return EXIT_SUCCESS;
  }
}
