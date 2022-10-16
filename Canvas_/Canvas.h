#ifndef CANVAS_H
#define CANVAS_H
#include "../DataStructures/Matrix.h"
#include "../Ilumination/Color.h"

template <int l,int k>
class Canvas{
    public:
      Canvas(Matrix<Color,l,k> * rgb);
      Canvas();
      bool setColorAt(int x, int y, Color c);
      Matrix<Color,l,k> * getCanvas();
      int getNumberLines();
      int getNumberColumns();
    private:
      int nLines;
      int nColumns;
      Matrix<Color,l,k> * canvas;
};
template <int l, int k>
Canvas<l,k>::Canvas(){}

template <int l, int k>
int Canvas<l,k>::getNumberLines(){
  return this->nLines;
}
template <int l, int k>
int Canvas<l,k>::getNumberColumns(){
  return this->nColumns;
}
template <int l, int k>
Canvas<l,k>::Canvas(Matrix<Color,l,k> *rgb){
  this->nLines = l;
  this->nColumns = k;

  (this->canvas) = rgb;
}

template <int l, int k>
Matrix<Color,l,k> * Canvas<l,k>::getCanvas(){
  return (this->canvas);
}
template <int l, int k>
bool Canvas<l,k>::setColorAt(int x, int y, Color c){
  return (*this->canvas).setVal(x,y,c); 
}

#endif