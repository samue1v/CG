#ifndef VECTOR_H
#define VECTOR_H
#include "Coordinate.h"
#include <iostream>

class Vector {
public:
  Vector();
  Vector(double x, double y, double z);
  Vector(Coordinate cord);
  double getLength();
  double getElementAt(int index);
  bool setLength(double);
  double *getVector();
  bool setVector(double x, double y, double z);
  bool setVector(Coordinate cord);
  double calcLength();
  void normalize();
  static double dot(Vector a, Vector b) {
    double *pa = a.getVector();
    double *pb = b.getVector();

    return pa[0] * pb[0] + pa[1] * pb[1] + pa[2] * pb[2];
  }
  static Vector cross(Vector a, Vector b) {
    double cx = (a.getElementAt(1)*b.getElementAt(2)) - (a.getElementAt(2)*b.getElementAt(1));
    double cy = (a.getElementAt(2)*b.getElementAt(0)) - (a.getElementAt(0)*b.getElementAt(2));
    double cz = (a.getElementAt(0)*b.getElementAt(1)) - (a.getElementAt(1)*b.getElementAt(0));
    return Vector(cx,cy,cz);
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
  Vector operator*(double right) {
    return Vector(vector[0] * right, vector[1] * right, vector[2] * right);
  }
  Vector operator/(double right) {
    Vector v = Vector(vector[0] / right, vector[1] / right, vector[2] / right);
    return v;
  }
  Vector operator+(double right){
    Vector v = Vector(vector[0] + right, vector[1] + right, vector[2] + right);
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
  double vector[3];
  double lenght;
  int maxIndex;
};

#endif