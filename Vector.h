#ifndef VECTOR_H
#define VECTOR_H
#include "Coordinate.h"

class Vector {
public:
  Vector();
  Vector(float x, float y, float z);
  Vector(Coordinate cord);
  int getLength();
  int getElementAt(int index);
  bool setLength(int);
  int *getVector();
  bool setVector(float x, float y, float z);
  bool setVector(Coordinate cord);
  static float dot(Vector a, Vector b){
    int * pa = a.getVector();
    int * pb = b.getVector();
  
    return pa[0] * pb[0] + pa[1] * pb[1] + pa[2] * pb[2];
    }
  Vector operator/(Vector right) {
    return Vector(vector[0] / right.getElementAt(0), vector[1] - right.getElementAt(1), vector[2] - right.getElementAt(2));
  }
  Vector operator*(float right) {
    return Vector(vector[0] * right, vector[1] * right, vector[2] * right);
  }

private:
  int vector[3];
  int lenght;
};

#endif