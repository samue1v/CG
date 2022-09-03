  #include "Color.h"
  
  Color::Color(){}
  Color::Color(int red, int green, int blue){
    this->red = red & 0xFF;
    this->green = green & 0xFF;
    this->blue = blue & 0xFF;
  }