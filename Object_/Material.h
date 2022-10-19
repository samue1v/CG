#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Ilumination/Reflect.h"
#include <stdio.h>

struct Material {
private:
  AmbientReflectiveness ka;
  DifuseReflectiveness kd;
  SpecularReflectiveness ke;

public:
  virtual AmbientReflectiveness getKa() = 0;
  virtual DifuseReflectiveness getKd() = 0;
  virtual SpecularReflectiveness getKe() = 0;
};

struct Rubber : Material {
public:
  Rubber()
      : ka(AmbientReflectiveness(Coeficients{0.7, 0.2, 0.2})),
        kd(DifuseReflectiveness(Coeficients(0.7, 0.2, 0.2))),
        ke(SpecularReflectiveness(Coeficients(0.7, 0.2, 0.2), 10)){};

  AmbientReflectiveness getKa();
  DifuseReflectiveness getKd();
  SpecularReflectiveness getKe();

private:
  AmbientReflectiveness ka;
  DifuseReflectiveness kd;
  SpecularReflectiveness ke;
};

struct Metal : Material {
public:
  Metal()
      : ka(AmbientReflectiveness(Coeficients{0.2, 0.7, 0.2})),
        kd(DifuseReflectiveness(Coeficients(0.2, 0.7, 0.2))),
        ke(SpecularReflectiveness(Coeficients(0,0,0), 1)){};

  AmbientReflectiveness getKa();
  DifuseReflectiveness getKd();
  SpecularReflectiveness getKe();

private:
  AmbientReflectiveness ka;
  DifuseReflectiveness kd;
  SpecularReflectiveness ke;
};

struct Plastic : Material {
public:
  Plastic()
      : ka(AmbientReflectiveness(Coeficients{0.3, 0.3, 0.7})),
        kd(DifuseReflectiveness(Coeficients(0.3, 0.3, 0.7))),
        ke(SpecularReflectiveness(Coeficients(0,0,0), 1)){};

  AmbientReflectiveness getKa();
  DifuseReflectiveness getKd();
  SpecularReflectiveness getKe();

private:
  AmbientReflectiveness ka;
  DifuseReflectiveness kd;
  SpecularReflectiveness ke;
};

struct Cooper : Material {
public:
  Cooper()
      : ka(AmbientReflectiveness(Coeficients{0.2, 0.3, 0.8})),
        kd(DifuseReflectiveness(Coeficients(0.2, 0.3, 0.8))),
        ke(SpecularReflectiveness(Coeficients(0.2, 0.3, 0.8), 1)){};

  AmbientReflectiveness getKa();
  DifuseReflectiveness getKd();
  SpecularReflectiveness getKe();

private:
  AmbientReflectiveness ka;
  DifuseReflectiveness kd;
  SpecularReflectiveness ke;
};

struct Marble : Material {
public:
  Marble()
      : ka(AmbientReflectiveness(Coeficients{0.8, 0.3, 0.2})),
        kd(DifuseReflectiveness(Coeficients(0.8, 0.3, 0.2))),
        ke(SpecularReflectiveness(Coeficients(0.8, 0.3, 0.2), 1)){};

  AmbientReflectiveness getKa();
  DifuseReflectiveness getKd();
  SpecularReflectiveness getKe();

private:
  AmbientReflectiveness ka;
  DifuseReflectiveness kd;
  SpecularReflectiveness ke;
};

#endif
