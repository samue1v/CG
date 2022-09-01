#include <stdio.h>
#include "ds.h"

class Canvas{
    public:
      Canvas(Matrix<Color> *rgb);
      Canvas();
      bool setColorAt(int x, int y, Color c);
      Matrix<Color> & getCanvas();
    private:
      Matrix<Color> canvas;
};



Canvas::Canvas(Matrix<Color> *rgb){
  this->canvas = *(rgb);
}

Matrix<Color> & Canvas::getCanvas(){
  return this->canvas;
}

bool Canvas::setColorAt(int x, int y, Color c){
  return this->canvas.setVal(x,y,c);  //retorna true
}
