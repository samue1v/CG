#include <stdio.h>
#include "Vector.h"
#include <math.h>
Vector::Vector(){};

Vector::Vector(float x, float y, float z) : lenght(1){
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

int Vector::getLength(){
  return this->lenght;
}

bool Vector::setLength(int newLength){
  if(newLength>0){
    this->lenght = newLength;
    return true;
  }
  return false;
}

int Vector::getElementAt(int index){
  if(index>lenght){
    return false;
  }
  return vector[index];
}

float Vector::length(){
  Vector v = *this;
  return sqrt(Vector::dot(v, v));
}