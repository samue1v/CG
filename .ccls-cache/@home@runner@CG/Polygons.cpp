
#include <stdio.h>
#include "Polygons.h"

Polygon::Polygon(){}

Circle::Circle(Coordinate center, float radius, Color color) : Polygon(){

  this->center = center;
  this->radius = radius;
  this->color = color;
}

bool Circle::setCenter(Coordinate newCenter) {
  this->center = newCenter;
  return true;
}

Coordinate Circle::getCenter() { return this->center; }

bool Circle::setRadius(float newRadius) {
  if (newRadius > 0) {
    this->radius = newRadius;
    return true;
  }
  return false;
}

int Circle::getRadius() { return this->radius; }

bool Circle::setColor(Color color) {
  this->color = color;
  return true;
}

Color Circle::getColor() { return this->color; }

