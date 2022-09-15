#ifndef REFLECT_H
#define REFLECT_H

//reflexao especular tem shininess


class Reflectiveness {
public:
  float kr;
  float kg;
  float kb;
  Reflectiveness();
  Reflectiveness(float kr, float kg, float kb);
};

class DifuseReflectiveness : Reflectiveness{
public:
  
  
}
#endif
