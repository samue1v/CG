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
      : ka(AmbientReflectiveness(Coeficients{1, 0, 0})),
        kd(DifuseReflectiveness(Coeficients(1, 0, 0))),
        ke(SpecularReflectiveness(Coeficients(1, 0, 0), 500)){};

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
      : ka(AmbientReflectiveness(Coeficients{1, 1, 1})),
        kd(DifuseReflectiveness(Coeficients(1, 1, 1))),
        ke(SpecularReflectiveness(Coeficients(1, 1, 1), 100)){};

  AmbientReflectiveness getKa();
  DifuseReflectiveness getKd();
  SpecularReflectiveness getKe();

private:
  AmbientReflectiveness ka;
  DifuseReflectiveness kd;
  SpecularReflectiveness ke;
};

#endif
