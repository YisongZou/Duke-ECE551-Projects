#include "circle.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

#define _USE_MATH_DEFINES

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  double Rsum = radius + otherCircle.radius;
  double area = 0;
  double pi = 3.14;
  if (d >= Rsum) {
    return area;
  }
  else if (radius - otherCircle.radius >= d) {
    area = pi * otherCircle.radius * otherCircle.radius;
    return area;
  }
  else if (otherCircle.radius - radius >= d) {
    area = pi * radius * radius;
    return area;
  }
  else {
    double area1 =
        radius * radius *
        acos((radius * radius + d * d - otherCircle.radius * otherCircle.radius) /
             (2 * radius * d));

    double area2 =
        otherCircle.radius * otherCircle.radius *
        acos((otherCircle.radius * otherCircle.radius + d * d - radius * radius) /
             (2 * otherCircle.radius * d));
    double cos = (radius * radius + d * d - otherCircle.radius * otherCircle.radius) /
                 (2 * radius * d);
    double sin = sqrt(1 - cos * cos);
    double area3 = radius * d * sin;

    area = area1 + area2 - area3;
    return area;
  }
  return area;
}
