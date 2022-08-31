#include "ds.h"
#include <stdio.h>

class Polygon {};

class Circle : Polygon {
private:
  Color color;
  int radius;
  Coordinate center;

public:
  Circle(Coordinate center, int radius, Color color);
  Color getColor();
  bool setColor(Color color);
  bool setRadius(int newRadius);
  int getRadius();
  bool setCenter(Coordinate newCenter);
  Coordinate getCenter();
};

Circle::Circle(Coordinate center, int radius, Color color) {
  this->center = center;
  this->radius = radius;
  this->color = color;
}

bool Circle::setCenter(Coordinate newCenter) {
  this->center = newCenter;
  return true;
}

Coordinate Circle::getCenter() { return this->center; }

bool Circle::setRadius(int newRadius) {
  if (newRadius > 0) {
    this->radius = newRadius;
    return true;
  }
  return false;
}

int Circle::getRadius() { return this->radius; }

bool Circle::setColor(Color color){
  this->color = color;
  return true;
}

Color Circle::getColor(){
  return this->color;
}