#include <stdio.h>
#include <stdlib.h>

#include "point.h"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(const Point & a, double & b) : center(a), radius(b) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
