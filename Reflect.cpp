#include "Reflect.h"

Reflectiveness::Reflectiveness() {}
Reflectiveness::Reflectiveness(float kr, float kg, float kb, float shininess=1){
  this->kr = kr;  
  this->kg = kg; 
  this->kb = kb;   
  this->shininess = shininess;
}