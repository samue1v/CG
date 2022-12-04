#ifndef INTENSITY_H
#define INTENSITY_H

#include "Reflect.h"
#include <iostream>

class Intensity {
public:
  Intensity();
  Intensity(double ir, double ig, double ib);
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
  friend std::ostream& operator<<(std::ostream& os, Intensity &i);

private:
  double ir;
  double ig;
  double ib;
};

#endif
