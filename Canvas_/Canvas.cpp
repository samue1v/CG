#include <stdio.h>
#include "Canvas.h"


Canvas::Canvas(){}

int Canvas::getNumberLines(){
  return this->l;
}

int Canvas::getNumberColumns(){
  return this->c;
}

Canvas::Canvas(Matrix<Color> *rgb,int l,int c){
  this->l = l;
  this->c = c;

  (this->canvas) = rgb;
}

Matrix<Color> * Canvas::getCanvas(){
  return (this->canvas);
}

bool Canvas::setColorAt(int x, int y, Color c){
  return (*this->canvas).setVal(x,y,c);  //retorna true
}
