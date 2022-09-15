#ifndef REFLECT_H
#define REFLECT_H

//reflexao especular tem shininess
#include "Intensity.h"
struct Coeficients{
  float kr;
  float kg;
  float kb;
};

class Reflectiveness {
public:
  Coeficients coefs;
  Intensity operator*(Intensity right) {
    return Intensity(coefs.kr * right.getRed(), coefs.kg * right.getGreen(), coefs.kb * right.getBlue());
  }
};

class DifuseReflectiveness : Reflectiveness{
public:
  DifuseReflectiveness();
  DifuseReflectiveness(float kr, float kg, float kb);
  
};


class AmbientReflectiveness : Reflectiveness{
public:
  AmbientReflectiveness();
  AmbientReflectiveness(float kr, float kg, float kb);
  
};

class SpecularReflectiveness : Reflectiveness{
public:
  SpecularReflectiveness();
  SpecularReflectiveness(float kr, float kg, float kb,int shininess);
  int shininess;
};
#endif
