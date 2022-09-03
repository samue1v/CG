#include <stdio.h>
#include "ds.h"


Vector::Vector(float x, float y, float z) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
}

Vector::Vector(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
}

int *Vector::getVector() { return this->vector; }

bool Vector::setVector(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
  return true;
}

bool Vector::setVector(float x, float y, float z) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
  return true;
}

float Vector::dot(Vector a, Vector b){
  int * pa = a.getVector();
  int * pb = b.getVector();
  
    return pa[0] * pb[0] + pa[1] * pb[1] + pa[2] * pb[2];
}