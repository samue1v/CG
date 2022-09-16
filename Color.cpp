  #include "Color.h"
  
  Color::Color(){}
  Color::Color(float red, float green, float blue){
    this->red = red;// & 0xFF000000;
    this->green = green;// & 0xFF000000;
    this->blue = blue;// & 0xFF000000;
  }
