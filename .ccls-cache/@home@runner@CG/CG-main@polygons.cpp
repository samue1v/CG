#include "ds.h"
#include <stdio.h>

class Polygon {};

class Circle : Polygon {
private:
  Color color;
  int radius;
  coordinate center;

public:
  Circle(coordinate center, int radius, Color color);
  bool setRadius(int newRadius);
  int getRadius();
  bool setCenter(coordinate newCenter);
  coordinate getCenter();
};

Circle::Circle(coordinate center, int radius, Color color) {
  this->center = center;
  this->radius = radius;
  this->color = color;
}

bool Circle::setCenter(coordinate newCenter) {
  this->center = newCenter;
  return true;
}

coordinate Circle::getCenter() { return this->center; }

bool Circle::setRadius(int newRadius) {
  if (newRadius > 0) {
    this->radius = newRadius;
    return true;
  }
  return false;
}

int Circle::getRadius() { return this->radius; }