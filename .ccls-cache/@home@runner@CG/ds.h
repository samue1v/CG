#ifndef DataStructHeader
#define DataStructHeader
#include <stdio.h>

const int INF = 10e8;
const unsigned char COLOR_MAX = '255';
const unsigned char COLOR_MIN = '255';
template <typename T> struct Pair {
  T left;
  T right;
};

struct Color {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
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
  int getVal(int x, int y);
  static float dot(Matrix a, Matrix b);

private:
  int nLines;
  int nColumns;
  T **matrix;
};

template <typename T> Matrix<T>::Matrix(int lines, int columns) {
  this->nLines = lines;
  this->nColumns = columns;
  int **m[lines];
  this->matrix = *m;
  for (int i = 0; i < lines; i++) {
    int c[columns];
    int *l = c;
    this->matrix[i] = l;
  }
}

template <typename T> int Matrix<T>::getVal(int x, int y) { return (this->matrix)[x][y]; }

template <typename T> bool Matrix<T>::setVal(int x, int y, T val) {
    (this->matrix)[x][y] = val;
    return true;
}

template <typename T> float Matrix<T>::dot(Matrix a, Matrix b) {
  if (!(a.nColumns == b.nColumns && a.nLines == b.nLines)) {
    printf("Erro na definição dos vetores: left_side: (%d,%d); right_side: (%d,%d)",
           a.nLines, a.nColumns, b.nLines, b.nColumns);
    return 0;
  } else {
    return a.getVal(0, 0) * b.getVal(0, 0) + a.getVal(1, 0) * b.getVal(1, 0) +
           a.getVal(2, 0) * b.getVal(2, 0);
  }
}

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
Vector::Vector(float x, float y, float z) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
}

Vector::Vector(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
}

int *Vector::getVector() { return this->vector; }

bool Vector::setVector(Coordinate cord) {
  this->vector[0] = cord.x;
  this->vector[1] = cord.y;
  this->vector[2] = cord.z;
  return true;
}

bool Vector::setVector(float x, float y, float z) {
  this->vector[0] = x;
  this->vector[1] = y;
  this->vector[2] = z;
  return true;
}

float Vector::dot(Vector a, Vector b){
  int * pa = a.getVector();
  int * pb = b.getVector();
  
    return pa[0] * pb[0] + pa[1] * pb[1] + pa[2] * pb[2];
}
#endif
