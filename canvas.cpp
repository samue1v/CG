#include <stdio.h>
#include "ds.h"

class Canvas{
    public:
      Canvas(Matrix rgb);
      Canvas(){};
    private:
      Matrix canvas;
        
};

Canvas::Canvas(Matrix rgb){
  this->canvas = rgb;
}
