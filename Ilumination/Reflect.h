#ifndef REFLECT_H
#define REFLECT_H

//reflexao especular tem shininess
struct Coeficients{
  Coeficients(){};
  Coeficients(float kr,float kg,float kb) : kr(kr),kg(kg),kb(kb){};
  float kr;
  float kg;
  float kb;
};

class Reflectiveness {
public:
  Coeficients coefs;
  Reflectiveness();
};

class DifuseReflectiveness : public Reflectiveness{
public:
  DifuseReflectiveness();
  DifuseReflectiveness(Coeficients coefs);

};


class AmbientReflectiveness : public Reflectiveness{
public:
  AmbientReflectiveness();
  AmbientReflectiveness(Coeficients coefs);

};

class SpecularReflectiveness : public Reflectiveness{
public:
  SpecularReflectiveness();
  SpecularReflectiveness(Coeficients coefs,int shininess);
  int shininess;
};
#endif
