  #include "Color.h"
  
  Color::Color(){}
  Color::Color(int red, int green, int blue){
    this->red = red;// & 0xFF000000;
    this->green = green;// & 0xFF000000;
    this->blue = blue;// & 0xFF000000;
  }
