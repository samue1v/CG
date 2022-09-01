#include <stdio.h>
#include "ds.h"

class Canvas{
    public:
      Canvas(Matrix<Color> *rgb,int l, int c);
      Canvas();
      bool setColorAt(int x, int y, Color c);
      Matrix<Color> * getCanvas();
      int getNumberLines();
      int getNumberColumns();
    private:
      int l;
      int c;
      Matrix<Color> canvas;
};


int Canvas::getNumberLines(){
  return this->l;
}

int Canvas::getNumberColumns(){
  return this->c;
}

Canvas::Canvas(Matrix<Color> *rgb,int l,int c){
  this->l = l;
  this->c = c;
  this->canvas = *(rgb);
}

Matrix<Color> * Canvas::getCanvas(){
  Matrix<Color> * m = &(this->canvas);
  return m;
}

bool Canvas::setColorAt(int x, int y, Color c){
  this->canvas.setVal(x,y,c);
}
