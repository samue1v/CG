
#ifndef CANVAS_H
#define CANVAS_H
#include "Matrix.h"
#include "Color.h"

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
      Matrix<Color> * canvas;
};

#endif