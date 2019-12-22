#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> map;
  map.add(60, 1);
  map.add(19, 2);
  map.add(93, 3);
  map.add(4, 4);
  map.add(25, 5);
  map.add(84, 6);
  map.add(1, 7);
  map.add(11, 8);
  map.add(21, 9);
  map.add(35, 10);
  map.add(70, 11);
  map.add(86, 12);
  std::cout << "done1\n";
  map.inorder();
  std::cout << "done2\n";
  std::cout << "\n";
  std::cout << "done3\n";
  int ans1 = map.lookup(60);
  std::cout << "done4\n";
  int ans2 = map.lookup(35);
  std::cout << "done5\n";
  map.remove(19);
  std::cout << "done6\n";
  map.inorder();
  std::cout << "done7\n";
  std::cout << "\n";
  std::cout << "ans1 should be 1 and =" << ans1 << "\n";
  std::cout << "ans2 should be 10 and =" << ans2 << "\n";

  BstMap<int, int> map2(map);
  std::cout << "map2\n";
  map2.inorder();
  BstMap<int, int> map3;
  map3.add(60, 1);
  map3.add(19, 2);
  map3.add(93, 3);
  map3.add(4, 4);
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
