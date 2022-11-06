#include <stdio.h>
#include "Vector.h"
#include <math.h>
#include "DataConsts.h"
Vector3D::Vector3D(){
  this->vector[0] = 0;
  this->vector[1] = 0;
  this->vector[2] = 0;
  this->maxIndex = 2;
}

Vector3D::Vector3D(double x, double y, double z) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
  this->lenght = this->calcLength();
  this->maxIndex = 2;
}

Vector3D::Vector3D(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
  this->lenght = this->calcLength();
  this->maxIndex = 2;
}

double *Vector3D::getVector() { return this->vector; }

bool Vector3D::setVector(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
  this->lenght = this->calcLength();
  return true;
}

bool Vector3D::setVector(double x, double y, double z) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
  this->lenght = this->calcLength();
  return true;
}

double Vector3D::getLength(){
  return this->lenght;
}

bool Vector3D::setLength(double newLength){
  if(newLength>0){
    this->lenght = newLength;
    return true;
  }
  return false;
}

double Vector3D::getElementAt(int index){
  if(index>this->maxIndex){
    return false;
  }
  return vector[index];
}

double Vector3D::calcLength(){
  Vector3D v = *this;
  return sqrt(Vector3D::dot(v, v));
}

void Vector3D::normalize(){
  this->vector[0] = (this->vector[0])/(this->lenght);
  this->vector[1] = (this->vector[1])/(this->lenght);
  this->vector[2] = (this->vector[2])/(this->lenght);
  this->lenght = 1;
}

std::ostream& operator<<(std::ostream& os,Vector3D& e){
    os <<"Vector3D:\n";
    os << "x: "<<e.getElementAt(0)<<" ";
    os << "y: "<<e.getElementAt(1)<<" ";
    os << "z: "<<e.getElementAt(2)<<" ";
    os<<"\n";
    return os;
}

Vector4D::Vector4D(){
  this->vector[0] = 0;
  this->vector[1] = 0;
  this->vector[2] = 0;
  this->vector[3] = 1;
  this->maxIndex = 3;
}

Vector4D::Vector4D(double x, double y, double z) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
  this->vector[3] = 1;
  this->lenght = this->calcLength();

  this->maxIndex = 3;
}

Vector4D::Vector4D(Vector3D v3d){
    this->vector[0] = v3d.getElementAt(0);
    this->vector[1] = v3d.getElementAt(1);
    this->vector[2] = v3d.getElementAt(2);
    this->vector[3] = 1;
    this->lenght = this->calcLength();
    this->maxIndex = 3;
}

Vector4D::Vector4D(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
  this->vector[3] = 1;
  this->lenght = this->calcLength();

  this->maxIndex = 3;
}

double *Vector4D::getVector() { return this->vector; }

bool Vector4D::setVector(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
  this->lenght = this->calcLength();
  return true;
}

bool Vector4D::setVector(double x, double y, double z,double h) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
  this->vector[3] = h;
  this->lenght = this->calcLength();
  return true;
}

double Vector4D::getLength(){
  return this->lenght;
}

bool Vector4D::setLength(double newLength){
  if(newLength>0){
    this->lenght = newLength;
    return true;
  }
  return false;
}

double Vector4D::getElementAt(int index){
  if(index>this->maxIndex){
    return false;
  }
  return vector[index];
}

double Vector4D::calcLength(){
  Vector4D v = *this;
  return sqrt(Vector4D::dot(v, v));
}

void Vector4D::normalize(){
  this->vector[0] = (this->vector[0])/(this->lenght);
  this->vector[1] = (this->vector[1])/(this->lenght);
  this->vector[2] = (this->vector[2])/(this->lenght);
  this->lenght = 1;
}

std::ostream& operator<<(std::ostream& os,Vector4D& e){
    os <<"Vector3D:\n";
    os << "x: "<<e.getElementAt(0)<<" ";
    os << "y: "<<e.getElementAt(1)<<" ";
    os << "z: "<<e.getElementAt(2)<<" ";
    os << "w: "<<e.getElementAt(3)<<" ";
    os<<"\n";
    return os;
}