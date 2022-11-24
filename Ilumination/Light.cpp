#include "Light.h"
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include <iostream>
#include <math.h>

//lembrar de limpar  a classe base

Light::Light() {}

AmbientLight::AmbientLight(){}

AmbientLight::AmbientLight(Intensity intensity) : intensity(intensity) {}

Intensity AmbientLight::getIntensity() { return this->intensity; }

bool AmbientLight::setIntensity(Intensity i) {
  if (i.getRed() > INTENSITY_MAX || i.getRed() < INTENSITY_MIN ||
      i.getGreen() > INTENSITY_MAX || i.getGreen() < INTENSITY_MIN ||
      i.getBlue() > INTENSITY_MAX || i.getBlue() < INTENSITY_MIN) {
    return false;
  }
  this->intensity = i;
  return true;
}

Intensity AmbientLight::calcIntensity(Coordinate P, Vector3D N, Vector3D V,
                                      Material *material) {
  return this->intensity*material->getKa();
}

Vector3D AmbientLight::calcDirection(Coordinate O){
  return Vector3D();
}

Vector3D AmbientLight::getReference(){
  return Vector3D();
}

void AmbientLight::applyViewTransform(Matrix<double,4,4> transformMatrix){

}

DirectionalLight::DirectionalLight() {}

DirectionalLight::DirectionalLight(Intensity intensity, Vector3D direction)
    : intensity(intensity), direction(direction) {}

Intensity DirectionalLight::calcIntensity(Coordinate P, Vector3D N, Vector3D V,
                                          Material *material) {
  Vector3D L = this->direction;
  Intensity i = Intensity();
  double n_dot_l = Vector3D::dot(N, L);
  if (n_dot_l > 0) {
    i = i + this->getIntensity() * material->getKd() * n_dot_l;
  }
  Vector3D R = N * 2.0f * Vector3D::dot(N, L) - L;
  double r_dot_l = Vector3D::dot(R, L);
  if (r_dot_l > 0) {
    i = i + this->getIntensity() * material->getKe() * r_dot_l;
  }

  return i;
}

Intensity DirectionalLight::getIntensity() { return this->intensity; }

bool DirectionalLight::setIntensity(Intensity i) {
  if (i.getRed() > INTENSITY_MAX || i.getRed() < INTENSITY_MIN ||
      i.getGreen() > INTENSITY_MAX || i.getGreen() < INTENSITY_MIN ||
      i.getBlue() > INTENSITY_MAX || i.getBlue() < INTENSITY_MIN) {
    return false;
  }
  this->intensity = i;
  return true;
}

Vector3D DirectionalLight::getDirection() { return this->direction; }

bool DirectionalLight::setDirection(Vector3D newVector) {
  this->direction = newVector;
  return true;
}

Vector3D DirectionalLight::calcDirection(Coordinate o){
  return this->direction*-1.0f;
}

Vector3D DirectionalLight::getReference(){
  return Vector3D();
}

void DirectionalLight::applyViewTransform(Matrix<double,4,4> transformMatrix){
  
}

PointLight::PointLight() {}

PointLight::PointLight(Intensity intensity, Coordinate position)
    : intensity(intensity), position(position) {}

Intensity PointLight::calcIntensity(Coordinate P, Vector3D N, Vector3D V,
                                    Material *material) {
  Intensity i = Intensity();
  Vector3D L = Vector3D(this->position - P);
  L.normalize();
  double n_dot_l = Vector3D::dot(N, L);
  if (n_dot_l > 0) {
    i = i + (this->intensity * material->getKd() * n_dot_l);
  }
  Vector3D R = (N * 2.0f * Vector3D::dot(N, L)) - L;
  R.normalize();
  double r_dot_v = Vector3D::dot(R, V);
  if (r_dot_v > 0) {
    i = i + (this->intensity * material->getKe() *
                pow(r_dot_v, material->getKe().shininess));
  }

  return i;
}

Intensity PointLight::getIntensity() { return this->intensity; }

bool PointLight::setIntensity(Intensity i) {
  if (i.getRed() > INTENSITY_MAX || i.getRed() < INTENSITY_MIN ||
      i.getGreen() > INTENSITY_MAX || i.getGreen() < INTENSITY_MIN ||
      i.getBlue() > INTENSITY_MAX || i.getBlue() < INTENSITY_MIN) {
    return false;
  }
  this->intensity = i;
  return true;
}

Coordinate PointLight::getPosition() { return this->position; }

bool PointLight::setPosition(Coordinate newVector) {
  this->position = newVector;
  return true;
}

Vector3D PointLight::calcDirection(Coordinate O){
  Vector3D dr = Vector3D(this->position - O);
  return dr;
}

Vector3D PointLight::getReference(){
  return this->position;
}

void PointLight::applyViewTransform(Matrix<double,4,4> transformMatrix){
  
}