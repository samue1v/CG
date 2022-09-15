#include "Reflect.h"

DifuseReflectiveness::DifuseReflectiveness() {}
DifuseReflectiveness::DifuseReflectiveness(float kr, float kg, float kb){
  this->coefs.kr = kr;  
  this->coefs.kg = kg; 
  this->coefs.kb = kb;   
}

AmbientReflectiveness::AmbientReflectiveness() {}
AmbientReflectiveness::AmbientReflectiveness(float kr, float kg, float kb){
  this->coefs.kr = kr;  
  this->coefs.kg = kg; 
  this->coefs.kb = kb;   
}

SpecularReflectiveness::SpecularReflectiveness() {}
SpecularReflectiveness::SpecularReflectiveness(float kr, float kg, float kb,int shininess){
  this->coefs.kr = kr;  
  this->coefs.kg = kg; 
  this->coefs.kb = kb;   
  this->shininess = shininess;
}

