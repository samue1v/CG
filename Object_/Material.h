#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Ilumination/Reflect.h"
#include <stdio.h>

struct Material {
protected:
  AmbientReflectiveness ka;
  DifuseReflectiveness kd;
  SpecularReflectiveness ke;

public:
  AmbientReflectiveness getKa();
  DifuseReflectiveness getKd();
  SpecularReflectiveness getKe();
  bool setKa(AmbientReflectiveness newKa);
  bool setKd(DifuseReflectiveness newKd);
  bool setKe(SpecularReflectiveness newKe);
};

struct Rubber : public Material {
public:
  Rubber(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.6, 0.6, 0.6)));
      this->ke = (SpecularReflectiveness(Coeficients(0.2, 0.2, 0.2), 300));
  }
};

struct Metal : public Material {
public:
  Metal(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.6, 0.6, 0.6)));
      this->ke = (SpecularReflectiveness(Coeficients(0.2, 0.2, 0.2), 300));
  }
};

struct Plastic : public Material {
public:
  Plastic(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.6, 0.6, 0.6)));
      this->ke = (SpecularReflectiveness(Coeficients(0.2, 0.2, 0.2), 300));
  }
};

struct Cooper : public Material {
public:
  Cooper(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.6, 0.6, 0.6)));
      this->ke = (SpecularReflectiveness(Coeficients(0.2, 0.2, 0.2), 300));
  }
};

struct Marble : public Material {
public:
  Marble(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.6, 0.6, 0.6)));
      this->ke = (SpecularReflectiveness(Coeficients(0.2, 0.2, 0.2), 300));
  }
};

#endif
