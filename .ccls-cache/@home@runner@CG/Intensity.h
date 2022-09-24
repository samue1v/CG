#ifndef INTENSITY_H
#define INTENSITY_H

#include "Reflect.h"

class Intensity {
public:
  Intensity(float ir=0, float ig=0, float ib=0);
  float getRed();
  bool setRed(float red);
  float getGreen();
  bool setGreen(float green);
  float getBlue();
  bool setBlue(float blue);
  Intensity operator*(float right) {
    return Intensity(ir * right, ig * right, ib * right);
  }

  Intensity operator*(Reflectiveness right) {
    return Intensity(right.coefs.kr * ir, right.coefs.kg * ig, right.coefs.kb * ib);
  }

  Intensity operator+(Intensity right) {
    return Intensity(ir + right.getRed(), ig + right.getGreen(), ib + right.getBlue());
  }
private:
  float ir;
  float ig;
  float ib;
};


#endif
