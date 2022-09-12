#ifndef COLOR_H
#define COLOR_H

struct Color {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  Color();
  Color(int red, int green, int blue);
  Color operator*(float right) {
    return Color(red * right, green * right, blue * right);
  }
};
#endif
