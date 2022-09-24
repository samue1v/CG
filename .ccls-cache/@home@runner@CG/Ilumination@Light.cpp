#include "Light.h"
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include <iostream>

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

Intensity Light::calcIntensity(Coordinate, Vector) { return 1.0; }

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

Intensity AmbientLight::calcIntensity(Coordinate P, Vector N) {
  // std::cout << this->intensity;
  return this->getIntensity();
}

DirectionalLight::DirectionalLight() {}

DirectionalLight::DirectionalLight(Intensity intensity, Vector direction)
    : intensity(intensity), direction(direction) {}

Intensity DirectionalLight::calcIntensity(Coordinate P, Vector N) {
  Vector L = this->direction;
  float n_dot_l = Vector::dot(N, L);
  if (n_dot_l < 0) {
    return 0;
  }
  return this->getIntensity() * n_dot_l;
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

Intensity PointLight::calcIntensity(Coordinate P, Vector N) {
  Vector L = Vector(this->position - P);
  L.normalize();
  float n_dot_l = Vector::dot(N, L); //*-1.0f);
  if (n_dot_l < 0.0) {
    return Intensity();
  }
  return this->getIntensity() * n_dot_l; // /(N.getLength()*L.getLength());
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