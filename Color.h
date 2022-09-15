#ifndef COLOR_H
#define COLOR_H
#include "Reflect.h"
#include "Intensity.h"
struct Color {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  Color();
  Color(int red, int green, int blue);
  Color operator*(float right) {
    return Color(red * right, green * right, blue * right);
  }
  Color operator*(Intensity right) {
    return Color(red * right.getRed(), green * right.getGreen(), blue * right.getBlue());
  }
};
#endif
