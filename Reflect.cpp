#include "Reflect.h"

Reflectiveness::Reflectiveness(){}

DifuseReflectiveness::DifuseReflectiveness() {}
DifuseReflectiveness::DifuseReflectiveness(Coeficients coefs){
  this->coefs = coefs;   
}

AmbientReflectiveness::AmbientReflectiveness() {}
AmbientReflectiveness::AmbientReflectiveness(Coeficients coefs){
  this->coefs = coefs;
}

SpecularReflectiveness::SpecularReflectiveness() {}
SpecularReflectiveness::SpecularReflectiveness(Coeficients coefs,int shininess){
  this->coefs = coefs;   
  this->shininess = shininess;
}

