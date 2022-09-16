#include <stdio.h>
#include "Intensity.h"


Intensity::Intensity(float red, float green, float blue): ir(red), ig(green), ib(blue) {}

float Intensity::getRed(){
  return this->ir;
}

bool Intensity::setRed(float red){
  if(red<0 || red>1){
    return false;
  }
  this->ir = red;
  return true;
}

float Intensity::getGreen(){
  return this->ig;
}

bool Intensity::setGreen(float green){
  if(green<0 || green>1){
    return false;
  }
  this->ig = green;
  return true;
}

float Intensity::getBlue(){
  return this->ib;
}

bool Intensity::setBlue(float blue){
  if(blue<0 || blue>1){
    return false;
  }
  this->ib = blue;
  return true;
}
