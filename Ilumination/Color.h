#ifndef COLOR_H
#define COLOR_H
#include "Reflect.h"
#include "Intensity.h"
#include <iostream>
struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  bool hasInit;
  Color();
  Color(uint8_t red, uint8_t green, uint8_t blue);
  Color operator*(uint8_t right) {
    return Color((red * right), (green * right),(blue * right));
  }
  Color operator*(Intensity right) {
    return Color((red * right.getRed()), (green * right.getGreen()), (blue * right.getBlue()));
  }
  friend std::ostream& operator<<(std::ostream& os, Color &c);
};
#endif
