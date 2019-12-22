#include "vector.hpp"

#include <cmath>
#include <cstdio>

double Vector2D::getMagnitude() const {
  double Mag = 0;
  Mag = std::sqrt(x * x + y * y);
  return Mag;
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D result;
  result.x = x + rhs.x;
  result.y = y + rhs.y;
  return result;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  double result;
  result = x * rhs.x + y * rhs.y;
  return result;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}

/* write your class implementation in this file
 */
