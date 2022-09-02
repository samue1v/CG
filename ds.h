#ifndef DataStructHeader
#define DataStructHeader
#include <stdio.h>

const int INF = 10e8;
const unsigned char COLOR_MAX = 0xFF & 255;
const unsigned char COLOR_MIN = 0xFF & 255;
template <typename T> struct Pair {
  T left;
  T right;
};

struct Color {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  Color(){};
  Color(int red, int green, int blue){
    this->red = red & 0xFF;
    this->green = green & 0xFF;
    this->blue = blue & 0xFF;
  }
};

struct Coordinate {
  float x;
  float y;
  float z;

  Coordinate(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Coordinate() {}

  static float dot(Coordinate a, Coordinate b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }
  Coordinate operator-(Coordinate right) {
    return Coordinate(x - right.x, y - right.y, z - right.z);
  }
};

template <typename T >class Matrix {
public:
  Matrix(int lines, int columns);
  Matrix(){};
  bool setVal(int x, int y, T val);
  T getVal(int x, int y);
  static float dot(Matrix a, Matrix b);

private:
  int nLines;
  int nColumns;
  T **matrix;
};


class Vector {
public:
  Vector(float x, float y, float z);
  Vector(Coordinate cord);
  int *getVector();
  bool setVector(float x, float y, float z);
  bool setVector(Coordinate cord);
  static float dot(Vector a, Vector b); 

private:
  int vector[3];
};

#endif
