#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <cstdio>
#include <cstdlib>

template<typename R, typename A>
class Function {
 public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};
#endif
