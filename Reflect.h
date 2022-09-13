#ifndef REFLECT_H
#define REFLECT_H

struct Reflectiveness {
  float kr;
  float kg;
  float kb;
  float shininess;
  Reflectiveness();
  Reflectiveness(float kr, float kg, float kb, float shininess=1);
  Reflectiveness operator*(float right) {
    return Reflectiveness(kr * right, kg * right, kb * right, shininess);
  }
};
#endif
