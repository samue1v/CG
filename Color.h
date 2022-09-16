#ifndef COLOR_H
#define COLOR_H
#include "Reflect.h"
#include "Intensity.h"
struct Color {
  float red;
  float green;
  float blue;
  Color();
  Color(float red, float green, float blue);
  Color operator*(float right) {
    return Color(red * right, green * right, blue * right);
  }
  Color operator*(Intensity right) {
    return Color(red * right.getRed(), green * right.getGreen(), blue * right.getBlue());
  }
};
#endif
