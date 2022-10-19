#include <stdio.h>
#include "Vector.h"
#include <math.h>
#include "DataConsts.h"
Vector::Vector(){
  this->vector[0] = 0;
  this->vector[1] = 0;
  this->vector[2] = 0;
  this->maxIndex = 2;
}

Vector::Vector(double x, double y, double z) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
  this->lenght = this->calcLength();
  this->maxIndex = 2;
}

Vector::Vector(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
  this->lenght = this->calcLength();
  this->maxIndex = 2;
}

double *Vector::getVector() { return this->vector; }

bool Vector::setVector(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
  this->lenght = this->calcLength();
  return true;
}

bool Vector::setVector(double x, double y, double z) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
  this->lenght = this->calcLength();
  return true;
}

double Vector::getLength(){
  return this->lenght;
}

bool Vector::setLength(double newLength){
  if(newLength>0){
    this->lenght = newLength;
    return true;
  }
  return false;
}

double Vector::getElementAt(int index){
  if(index>this->maxIndex){
    return false;
  }
  return vector[index];
}

double Vector::calcLength(){
  Vector v = *this;
  return sqrt(Vector::dot(v, v));
}

void Vector::normalize(){
  this->vector[0] = (this->vector[0])/(this->lenght);
  this->vector[1] = (this->vector[1])/(this->lenght);
  this->vector[2] = (this->vector[2])/(this->lenght);
  this->lenght = 1;
}