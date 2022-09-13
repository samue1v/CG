#include "Light.h"
#include "Coordinate.h"
#include <iostream>

Light::Light(){}

float Light::getIntensity(){
    return this->intensity;
}

bool Light::setIntensity(float i){
    if(i<0){
        return false;
    }
    this->intensity = i;
    return true;
}

float Light::calcIntensity(Coordinate, Vector){return 1.0;}

AmbientLight::AmbientLight(){};



AmbientLight::AmbientLight(float intensity) : intensity(intensity){}

float AmbientLight::getIntensity(){
    return this->intensity;
}

bool AmbientLight::setIntensity(float i){
    if(i<0){
        return false;
    }
    this->intensity = i;
    return true;
}


float AmbientLight::calcIntensity(Coordinate P,Vector N){
    //std::cout << this->intensity;
    return this->getIntensity();
}

DirectionalLight::DirectionalLight(){}

DirectionalLight::DirectionalLight(float intensity,Vector direction) : intensity(intensity),direction(direction){}

float DirectionalLight::calcIntensity(Coordinate P,Vector N){
    Vector L = this->direction;
    float n_dot_l = Vector::dot(N,L);
    if(n_dot_l<=0){
        return 0;
    }
    float m = this->getIntensity()*n_dot_l/(N.getLength()*L.getLength());
    std::cout << n_dot_l <<'\n';
    return this->getIntensity()*n_dot_l/(N.getLength()*L.getLength());
}

float DirectionalLight::getIntensity(){
    return this->intensity;
}

bool DirectionalLight::setIntensity(float i){
    if(i<0){
        return false;
    }
    this->intensity = i;
    return true;
}

Vector DirectionalLight::getDirection(){
    return this->direction;
}

bool DirectionalLight::setDirection(Vector newVector){
    this->direction = newVector;
    return true;

}

PointLight::PointLight(){}

PointLight::PointLight(float intensity, Coordinate position) : intensity(intensity),position(position){}

float PointLight::calcIntensity(Coordinate P,Vector N){
    Vector L = Vector(this->position - P);
    L.normalize();
    float n_dot_l = Vector::dot(N,L);
    if(n_dot_l<=0){
        return 0;
    }
    return this->getIntensity()*n_dot_l; // /(N.getLength()*L.getLength());
}

float PointLight::getIntensity(){
    return this->intensity;
}

bool PointLight::setIntensity(float i){
    if(i<0){
        return false;
    }
    this->intensity = i;
    return true;
}

Coordinate PointLight::getPosition(){
    return this->position;
}

bool PointLight::setPosition(Coordinate newVector){
    this->position = newVector;
    return true;

}