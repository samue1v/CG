#include "Intensity.h"
#include "../DataStructures/DataConsts.h"
#include <iostream>
#include <stdio.h>

Intensity::Intensity(){
  ir = 0;
  ig = 0;
  ib = 0;
}

Intensity::Intensity(float red, float green, float blue)
    : ir(red), ig(green), ib(blue) {}

float Intensity::getRed() { return this->ir; }

bool Intensity::setRed(float red) {
  if (red < 0 || red > 1) {
    return false;
  }
  this->ir = red;
  return true;
}

float Intensity::getGreen() { return this->ig; }

bool Intensity::setGreen(float green) {
  if (green < 0 || green > 1) {
    return false;
  }
  this->ig = green;
  return true;
}

float Intensity::getBlue() { return this->ib; }

bool Intensity::setBlue(float blue) {
  if (blue < 0 || blue > 1) {
    return false;
  }
  this->ib = blue;
  return true;
}

Intensity Intensity::normalize() {
  float bigger = -INF;
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