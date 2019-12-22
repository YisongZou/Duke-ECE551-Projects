#include "point.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double a;
  double b;
  a = (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
  b = sqrt(a);
  return b;
}
