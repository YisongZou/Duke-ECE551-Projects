#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main(void) {
  BstSet<int> map;
  map.add(60);
  map.add(19);
  map.add(93);
  map.add(4);
  map.add(25);
  map.add(84);
  map.add(1);
  map.add(11);
  map.add(21);
  map.add(35);
  map.add(70);
  map.add(86);
  std::cout << "done1\n";
  map.inorder();
  std::cout << "done2\n";
  std::cout << "\n";
  std::cout << "done3\n";
  bool ans1 = map.contains(60);
  std::cout << "done4\n";
  bool ans2 = map.contains(35);
  std::cout << "done5\n";
  map.remove(19);
  std::cout << "done6\n";
  map.inorder();
  std::cout << "done7\n";
  std::cout << "\n";
  std::cout << "ans1 should be 1 and =" << ans1 << "\n";
  std::cout << "ans2 should be 10 and =" << ans2 << "\n";

  BstSet<int> map2(map);
  std::cout << "map2\n";
  map2.inorder();
  BstSet<int> map3;
  map3.add(60);
  map3.add(19);
  map3.add(93);
  map3.add(4);
  map2 = map3;
  std::cout << "map2\n";
  map2.inorder();
  std::cout << "\n";
  std::cout << "map\n";
  map.inorder();
  std::cout << "map3\n";
  map3.inorder();
  return EXIT_SUCCESS;
}
