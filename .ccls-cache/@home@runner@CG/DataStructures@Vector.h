#ifndef VECTOR_H
#define VECTOR_H
#include "Coordinate.h"
#include <iostream>

class Vector {
public:
  Vector();
  Vector(float x, float y, float z);
  Vector(Coordinate cord);
  float getLength();
  float getElementAt(int index);
  bool setLength(float);
  float *getVector();
  bool setVector(float x, float y, float z);
  bool setVector(Coordinate cord);
  float calcLength();
  void normalize();
  static float dot(Vector a, Vector b) {
    float *pa = a.getVector();
    float *pb = b.getVector();

    return pa[0] * pb[0] + pa[1] * pb[1] + pa[2] * pb[2];
  }

  Vector operator/(Vector right) {
    return Vector(vector[0] / right.getElementAt(0),
                  vector[1] / right.getElementAt(1),
                  vector[2] / right.getElementAt(2));
  }
  Vector operator-(Vector right) {
    return Vector(vector[0] - right.getElementAt(0),
                  vector[1] - right.getElementAt(1),
                  vector[2] - right.getElementAt(2));
  }
  Vector operator*(float right) {
    return Vector(vector[0] * right, vector[1] * right, vector[2] * right);
  }
  Vector operator/(float right) {
    Vector v = Vector(vector[0] / right, vector[1] / right, vector[2] / right);
    return v;
  }

  /*
  Operadores:
  + : vetor+ponto -> ponto
  - : vetor-ponto -> ponto
  */
  Coordinate operator+(Coordinate right) {
    return Coordinate(vector[0] + right.x, vector[1] + right.y,
                      vector[2] + right.z);
  }
  Coordinate operator-(Coordinate right) {
    return Coordinate(vector[0] - right.x, vector[1] - right.y,
                      vector[2] - right.z);
  }

private:
  float vector[3];
  float lenght;
};

#endif