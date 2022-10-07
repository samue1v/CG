
#include "Shapes.h"
#include <iostream>
#include <stdio.h>

Shape3D::Shape3D() {}

Sphere::Sphere(Coordinate center, double radius, Material *material)
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

bool Sphere::setRadius(double newRadius) {
  if (newRadius > 0) {
    this->radius = newRadius;
    return true;
  }
  return false;
}

double Sphere::getRadius() { return this->radius; }

bool Sphere::setMaterial(Material *material) {
  this->material = material;
  return true;
}

double Sphere::IntersectRay(Coordinate O, Vector D,double tMin,double tMax) {
  double r = this->getRadius();
  Vector c_minus_o = Vector((O - this->getCenter()));
  double a = Vector::dot(D, D);
  double b = 2 * Vector::dot(c_minus_o, D);
  double c = Vector::dot(c_minus_o, c_minus_o) - r * r;

  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return INF;
  }

  double t1 = (-b + sqrt(discriminant)) / (2 * a);
  double t2 = (-b - sqrt(discriminant)) / (2 * a);

  if(t1>=tMin && t1<=tMax && t1<t2){
    return t1;
  }
  return t2;
}

Material *Sphere::getMaterial() { return (this->material); }

Vector Sphere::computeNormal(Coordinate P) {
  return Vector(P - (this->center));
}

Plane::Plane() {}

Plane::Plane(Coordinate planePoint, Vector normal, Material * material) {
  this->planePoint = planePoint;
  this->normal = normal;
  this->material = material;
}

Material *Plane::getMaterial() { return this->material; }

Vector Plane::computeNormal(Coordinate P){ return this->normal;}

double Plane::IntersectRay(Coordinate O, Vector D,double tMin,double tMax){
  Vector p_minuspi = Vector(this->planePoint - O);//mudei aqui
  double denom = Vector::dot(D,this->normal);
    double t = Vector::dot(p_minuspi,this->normal) / denom;
    if(t>=tMin && t<tMax){
  	 return t;
    }
	return INF;
}