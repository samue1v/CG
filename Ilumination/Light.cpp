#include "Light.h"
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include <iostream>


//lembrar de limpar  a classe base

Light::Light() {}

bool Light::setIntensity(Intensity i){
  if (i.getRed() > INTENSITY_MAX || i.getRed() < INTENSITY_MIN ||
      i.getGreen() > INTENSITY_MAX || i.getGreen() < INTENSITY_MIN ||
      i.getBlue() > INTENSITY_MAX || i.getBlue() < INTENSITY_MIN) {
    return false;
  }
  this->intensity = i;
  return true;
}

Intensity Light::getIntensity(){
  return this->intensity;
}

std::string Light::getName(){
  return this->name;
}

void Light::flipSwitch(){
  this->isOn = !isOn;
}

bool Light::getSwitchState(){
  return this->isOn;
}

LightType Light::getLightType(){
  return this->lightType;
}

AmbientLight::AmbientLight(){}

AmbientLight::AmbientLight(Intensity intensity,std::string name) {
  this->intensity = intensity;
  this->name = name;
  this->isOn = true;
  this->isAvaliable = true;
  this->lightType = ambient;
  }

Intensity AmbientLight::calcIntensity(Coordinate P, Vector3D N, Vector3D V,
                                      Material *material) {
  return this->intensity*material->getKa();
}

Vector3D AmbientLight::calcDirection(Coordinate O){
  return Vector3D();
}

bool AmbientLight::getAvaliable(){
  return this->isAvaliable;
}

void AmbientLight::applyViewTransform(Matrix<double,4,4> transformMatrix){

}

DirectionalLight::DirectionalLight() {}

DirectionalLight::DirectionalLight(Intensity intensity, Vector3D direction,std::string name) {
  this->direction = direction;
  this->intensity = intensity;
  this->name = name;
  this->isOn = true;
  this->isAvaliable = true;
  this->lightType = directional;
  }

Intensity DirectionalLight::calcIntensity(Coordinate P, Vector3D N, Vector3D V,
                                          Material *material) {
  Vector3D L = this->direction*-1.0;
  Intensity i = Intensity();
  double n_dot_l = Vector3D::dot(N, L);
  if (n_dot_l > 0) {
    i = i + (this->getIntensity() * material->getKd() * n_dot_l);
  }
  Vector3D R = (N * 2.0f * n_dot_l) - L;
  R.normalize();
  double r_dot_v = Vector3D::dot(R, V);
  if (r_dot_v > 0) {
    i = i + (this->intensity * material->getKe() *
                pow(r_dot_v, material->getKe().shininess));
  }
  return i;
}

Vector3D DirectionalLight::getDirection() { return this->direction; }

bool DirectionalLight::setDirection(Vector3D newVector) {
  this->direction = newVector;
  return true;
}

Vector3D DirectionalLight::calcDirection(Coordinate o){
  return this->direction*-1.0;
}

bool DirectionalLight::getAvaliable(){
  return this->isAvaliable;

}

void DirectionalLight::applyViewTransform(Matrix<double,4,4> transformMatrix){
  this->direction = (transformMatrix * Matrix<double,4,1>(direction)).toVector3D();
  //this->minu
}

PointLight::PointLight() {}

PointLight::PointLight(Intensity intensity, Coordinate position,std::string name){
  this->position = position;
  this->intensity = intensity;
  this->name = name;
  this->isOn = true;
  this->isAvaliable = true;
  this->lightType = point;
  }

Intensity PointLight::calcIntensity(Coordinate P, Vector3D N, Vector3D V,
                                    Material *material) {
  Intensity i = Intensity();
  Vector3D L = Vector3D(this->position - P);
  L.normalize();
  double n_dot_l = Vector3D::dot(N, L);
  if (n_dot_l > 0) {
    i = i + (this->intensity * material->getKd() * n_dot_l);
  }
  Vector3D R = (N * 2.0f * n_dot_l) - L;
  R.normalize();
  double r_dot_v = Vector3D::dot(R, V);
  if (r_dot_v > 0) {
    i = i + (this->intensity * material->getKe() *
                pow(r_dot_v, material->getKe().shininess));
  }

  return i;
}

bool PointLight::getAvaliable(){
  return this->isAvaliable;
}

Coordinate PointLight::getPosition() { return this->position; }

bool PointLight::setPosition(Coordinate newVector) {
  this->position = newVector;
  return true;
}

Vector3D PointLight::calcDirection(Coordinate O){
  
  return Vector3D(this->position - O);
}

void PointLight::applyViewTransform(Matrix<double,4,4> transformMatrix){
  this->position = (transformMatrix * Matrix<double,4,1>(position)).toCoordinate();
}

SpotLight::SpotLight(){}

SpotLight::SpotLight(Intensity intensity,Coordinate position,Vector3D direction,double angle,std::string name){
  this->intensity = intensity;
  this->position = position;
  this->direction = direction;
  if(angle > 90){
    angle = 90;
  }
  if(angle<0){
    angle = 0;
  }
  this->angle = (angle*PI)/180.0;
  this->name = name;
  this->isOn = true;
  this->isAvaliable = true;
  this->lightType = spot;

}

bool SpotLight::getAvaliable(){
  return this->isAvaliable;
}

Intensity SpotLight::getIntensity(){
  return this->intensity;
}

bool SpotLight::setIntensity(Intensity newIntensity){
  this->intensity = newIntensity;
  return true;
}

Intensity SpotLight::calcIntensity(Coordinate P, Vector3D N, Vector3D V,Material *material){
  Intensity i;
  Vector3D L = Vector3D(this->position - P);
  L.normalize();
  Vector3D minusDir = (this->direction)*-1.0;
  double cosAngle = (cos(this->angle)); 
  double n_dot_l = Vector3D::dot(N, L);
  double x = (Vector3D::dot(L,minusDir));
  Vector3D R = (N * 2.0f * n_dot_l) - L;
  R.normalize();
  double r_dot_v = Vector3D::dot(R, V);
  if (n_dot_l > 0 && x>cosAngle) {
    i = i + ((this->intensity*x)* material->getKd() * n_dot_l);
  }
  /*
  if(x>cosAngle){
    i = i + ((this->intensity*x) * material->getKd() * n_dot_l)+
                ((this->intensity*x) * material->getKe() * pow(r_dot_v, material->getKe().shininess));
  }*/
  if (r_dot_v > 0 && x>cosAngle) {
    i = i + ((this->intensity*x) * material->getKe() *
                pow(r_dot_v, material->getKe().shininess));
  }
  return i;
}

Vector3D SpotLight::calcDirection(Coordinate P){
  /*
  Vector3D L = Vector3D(this->position - P);
  double cosAngle = (cos(this->angle));
  L.normalize();
  double x = (Vector3D::dot(L,(this->direction)*-1.0));
  if(x>cosAngle){
    this->isAvaliable = false;
    return Vector3D();
  }*/
  return Vector3D(this->position - P);
}

std::string SpotLight::getName(){
  return this->name;
}

void SpotLight::applyViewTransform(Matrix<double,4,4> transformMatrix){
  this->position = (transformMatrix * Matrix<double,4,1>(position)).toCoordinate();
  this->direction = (transformMatrix * Matrix<double,4,1>(direction)).toVector3D();
}