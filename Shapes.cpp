
#include <stdio.h>
#include <iostream>
#include "Shapes.h"

Shape3D::Shape3D(){}

Circle::Circle(Coordinate center, float radius, Material * material) : Shape3D(){

  this->center = center;
  this->radius = radius;
  this->material = (material);
  std::cout << (material)->getKd().coefs.kr;
  std::cout << material->getKd().coefs.kr <<"\n";
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

bool Circle::setMaterial(Material * material) {
  this->material = material;
  return true;
}

Pair<float> Circle::IntersectRay(Coordinate O, Vector D){
    float r = this->getRadius();
    Vector c_minus_o = Vector((O - this->getCenter()));
    float a = Vector::dot(D, D);
    float b = 2 * Vector::dot(c_minus_o, D);
    float c = Vector::dot(c_minus_o, c_minus_o) - r*r;
    
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
      return {INF,INF};
    }

    float t1 = (-b + sqrt(discriminant)) / (2*a);
    float t2 = (-b - sqrt(discriminant)) / (2*a);
    return {t1, t2};
  }

Material * Circle::getMaterial() { return (this->material); }

