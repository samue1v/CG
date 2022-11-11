  #include "Color.h"

  Color::Color(){hasInit = false;}
  Color::Color(uint8_t red, uint8_t green, uint8_t blue){
    hasInit = true;
    this->red = red;// & 0xFF000000;
    this->green = green;// & 0xFF000000;
    this->blue = blue;// & 0xFF000000;
  }

  std::ostream& operator<<(std::ostream& os, Color &c){
  os<< "r:";
  os<< c.red;
  os<<"/";
  os<< "g:";
  os<< c.green;
  os<<"/";
  os<< "b:";
  os<< c.blue;
  os<<"/";
  return os;
}