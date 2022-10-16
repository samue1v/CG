#ifndef COLOR_H
#define COLOR_H
#include "Reflect.h"
#include "Intensity.h"
#include <iostream>
struct Color {
  double red;
  double green;
  double blue;
  Color();
  Color(double red, double green, double blue);
  Color operator*(double right) {
    return Color(red * right, green * right, blue * right);
  }
  Color operator*(Intensity right) {
    return Color(red * right.getRed(), green * right.getGreen(), blue * right.getBlue());
  }
  friend std::ostream& operator<<(std::ostream& os, Color &c);
};
#endif
