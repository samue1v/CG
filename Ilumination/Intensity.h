#ifndef INTENSITY_H
#define INTENSITY_H

#include "Reflect.h"
#include <iostream>

class Intensity {
public:
  Intensity();
  Intensity(float ir, float ig, float ib);
  float getRed();
  bool setRed(float red);
  float getGreen();
  bool setGreen(float green);
  float getBlue();
  bool setBlue(float blue);
  Intensity normalize();
  Intensity operator*(float right) {
    return Intensity(ir * right, ig * right, ib * right);
  }

  Intensity operator*(Reflectiveness right) {
    return Intensity(right.coefs.kr * ir, right.coefs.kg * ig,
                     right.coefs.kb * ib);
  }

  Intensity operator+(Intensity right) {
    return Intensity(ir + right.getRed(), ig + right.getGreen(),
                     ib + right.getBlue());
  }
  friend std::ostream& operator<<(std::ostream& os, Intensity &i);

private:
  float ir;
  float ig;
  float ib;
};

#endif
