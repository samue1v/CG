#ifndef COLOR_H
#define COLOR_H
#include "Reflect.h"
#include "Intensity.h"
#include <iostream>
struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  Color();
  Color(uint8_t red, uint8_t green, uint8_t blue);
  Color operator*(double right) {
    return Color((uint8_t)((double)red * right), (uint8_t)((double)green * right),(uint8_t)((double)blue * right));
  }
  Color operator*(Intensity right) {
    return Color((u_int8_t)((double)red * right.getRed()), (u_int8_t)((double)green * right.getGreen()), (uint8_t)((double)blue * right.getBlue()));
  }
  friend std::ostream& operator<<(std::ostream& os, Color &c);
};
#endif
