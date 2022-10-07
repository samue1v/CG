#ifndef INTENSITY_H
#define INTENSITY_H

#include "Reflect.h"

class Intensity {
public:
  Intensity(double ir = 0, double ig = 0, double ib = 0);
  double getRed();
  bool setRed(double red);
  double getGreen();
  bool setGreen(double green);
  double getBlue();
  bool setBlue(double blue);
  Intensity normalize();
  Intensity operator*(double right) {
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

private:
  double ir;
  double ig;
  double ib;
};

#endif
