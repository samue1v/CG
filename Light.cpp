#include "Light.h"
#include "Coordinate.h"

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

Coordinate AmbientLight::getPosition(){
    return this->position;
}

bool AmbientLight::setPosition(Coordinate newPosition){
    this->position = newPosition;
    return true;
}

float AmbientLight::calcIntensity(Coordinate P,Vector N){
    return this->getIntensity();
}

float DirectionalLight::calcIntensity(Coordinate P,Vector N){
    Vector L = this->direction;
    float n_dot_l = Vector::dot(N,L);
    return this->getIntensity()*n_dot_l/(N.getLength()*L.getLength());
}