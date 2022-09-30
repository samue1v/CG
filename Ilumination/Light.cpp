#include "Light.h"
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include <iostream>
#include <math.h>

Light::Light() {}

Intensity Light::getIntensity() { return this->intensity; }

bool Light::setIntensity(Intensity i) {
  if (i.getRed() > INTENSITY_MAX || i.getRed() < INTENSITY_MIN ||
      i.getGreen() > INTENSITY_MAX || i.getGreen() < INTENSITY_MIN ||
      i.getBlue() > INTENSITY_MAX || i.getBlue() < INTENSITY_MIN) {
    return false;
  }
  this->intensity = i;
  return true;
}

Intensity Light::calcIntensity(Coordinate, Vector, Vector, Material *) {
  return 1.0;
}

AmbientLight::AmbientLight(){};

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

Intensity AmbientLight::calcIntensity(Coordinate P, Vector N, Vector V,
                                      Material *material) {
  return this->getIntensity();
}

DirectionalLight::DirectionalLight() {}

DirectionalLight::DirectionalLight(Intensity intensity, Vector direction)
    : intensity(intensity), direction(direction) {}

Intensity DirectionalLight::calcIntensity(Coordinate P, Vector N, Vector V,
                                          Material *material) {
  Vector L = this->direction;
  Intensity i = Intensity();
  float n_dot_l = Vector::dot(N, L);
  if (n_dot_l > 0) {
    i = i + this->getIntensity() * material->getKd() * n_dot_l;
  }
  Vector R = N * 2.0f * Vector::dot(N, L) - L;
  float r_dot_l = Vector::dot(R, L);
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

Vector DirectionalLight::getDirection() { return this->direction; }

bool DirectionalLight::setDirection(Vector newVector) {
  this->direction = newVector;
  return true;
}

PointLight::PointLight() {}

PointLight::PointLight(Intensity intensity, Coordinate position)
    : intensity(intensity), position(position) {}

Intensity PointLight::calcIntensity(Coordinate P, Vector N, Vector V,
                                    Material *material) {
  Intensity i = Intensity();
  Vector L = Vector(this->position - P);
  L.normalize();
  float n_dot_l = Vector::dot(N, L);
  if (n_dot_l > 0) {
    i = i + this->getIntensity() * material->getKd() * n_dot_l;
  }
  Vector R = N * 2.0f * Vector::dot(N, L) - L;
  R.normalize();
  float r_dot_l = Vector::dot(R, L);
  if (r_dot_l > 0) {
    i = i + this->getIntensity() * material->getKe() *
                pow(r_dot_l, material->getKe().shininess);
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