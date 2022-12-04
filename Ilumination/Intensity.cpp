#include "Intensity.h"
#include "../DataStructures/DataConsts.h"
#include <iostream>
#include <stdio.h>

Intensity::Intensity(){
  ir = 0;
  ig = 0;
  ib = 0;
}

Intensity::Intensity(double red, double green, double blue)
    : ir(red), ig(green), ib(blue) {}

double Intensity::getRed() { return this->ir; }

bool Intensity::setRed(double red) {
  if (red < 0 || red > 1) {
    return false;
  }
  this->ir = red;
  return true;
}

double Intensity::getGreen() { return this->ig; }

bool Intensity::setGreen(double green) {
  if (green < 0 || green > 1) {
    return false;
  }
  this->ig = green;
  return true;
}

double Intensity::getBlue() { return this->ib; }

bool Intensity::setBlue(double blue) {
  if (blue < 0 || blue > 1) {
    return false;
  }
  this->ib = blue;
  return true;
}

Intensity Intensity::normalize() {
  double bigger = -INF;
  if (ir > bigger) {
    bigger = ir;
  }
  if (ig > bigger) {
    bigger = ig;
  }
  if (ib > bigger) {
    bigger = ib;
  }
  ir = ir / bigger;
  ig = ig / bigger;
  ib = ib / bigger;
  return Intensity(ir, ig, ib);
}


  std::ostream& operator<<(std::ostream& os, Intensity &i){
  os<< "ir:";
  os<< i.getRed();
  os<<"/";
  os<< "ig:";
  os<< i.getGreen();
  os<<"/";
  os<< "ib:";
  os<< i.getBlue();
  os<<"\n";
  return os;
}