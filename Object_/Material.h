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
      this->kd = (DifuseReflectiveness(Coeficients(0.8, 0.8, 0.8)));
      this->ke = (SpecularReflectiveness(Coeficients(0.8, 0.8, 0.8), 800));
  }
};

struct Plastic : public Material {
public:      
  Plastic(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.6, 0.6, 0.6)));
      this->ke = (SpecularReflectiveness(Coeficients(0.6, 0.6, 0.6), 600));
  }
};

struct Copper : public Material {
public:
  Copper(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.722, 0.451, 0.2)));
      this->ke = (SpecularReflectiveness(Coeficients(0.722, 0.451, 0.2), 800));
  }
};

struct Marble : public Material {
public:
  Marble(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.6, 0.6, 0.6)));
      this->ke = (SpecularReflectiveness(Coeficients(0.1, 0.1, 0.1), 200));
  }
};

struct Wood : public Material {
public:
  Wood(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.7, 0.7, 0.7)));
      this->ke = (SpecularReflectiveness(Coeficients(0.3, 0.3, 0.3), 400));
  }
};

struct Brick : public Material {
public:
  Brick(){
      this->ka = (AmbientReflectiveness(Coeficients{0.5, 0.5, 0.5}));
      this->kd = (DifuseReflectiveness(Coeficients(0.4*0.667, 0.4*0.29, 0.4*0.267)));
      this->ke = (SpecularReflectiveness(Coeficients(0.1*0.667, 0.1*0.29, 0.1*0.267), 100));
  }
};

struct BlueConcrete : public Material {
public:
  BlueConcrete(){
      this->ka = (AmbientReflectiveness(Coeficients{0.2, 0.5, 0.6}));
      this->kd = (DifuseReflectiveness(Coeficients(0.1, 0.2, 0.4)));
      this->ke = (SpecularReflectiveness(Coeficients(0, 0, 0), 0));
  }
};


#endif
