
#include "Shapes.h"
#include <iostream>
#include <stdio.h>

Shape3D::Shape3D() {}

Sphere::Sphere(Coordinate center, float radius, Material *material)
    : Shape3D() {

  this->center = center;
  this->radius = radius;
  this->material = (material);
}

bool Sphere::setCenter(Coordinate newCenter) {
  this->center = newCenter;
  return true;
}

Coordinate Sphere::getCenter() { return this->center; }

bool Sphere::setRadius(float newRadius) {
  if (newRadius > 0) {
    this->radius = newRadius;
    return true;
  }
  return false;
}

int Sphere::getRadius() { return this->radius; }

bool Sphere::setMaterial(Material *material) {
  this->material = material;
  return true;
}

Pair<float> Sphere::IntersectRay(Coordinate O, Vector D) {
  float r = this->getRadius();
  Vector c_minus_o = Vector((O - this->getCenter()));
  float a = Vector::dot(D, D);
  float b = 2 * Vector::dot(c_minus_o, D);
  float c = Vector::dot(c_minus_o, c_minus_o) - r * r;

  float discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return {INF, INF};
  }

  float t1 = (-b + sqrt(discriminant)) / (2 * a);
  float t2 = (-b - sqrt(discriminant)) / (2 * a);
  return {t1, t2};
}

Material *Sphere::getMaterial() { return (this->material); }

Vector Sphere::computeNormal(Coordinate P){
	  return Vector(P - (this->center));
}

Plane::Plane(){}

Plane::Plane(Coordinate topLeftCorner,Vector normal, float width, float height){
	this->topLeftCorner = topLeftCorner; 
	this->normal = normal;
	this->width = width;
	this->height = height;
}