#ifndef VECTOR_H
#define VECTOR_H
#include "Coordinate.h"
#include <iostream>

class Vector3D {
public:
  Vector3D();
  Vector3D(double x, double y, double z);
  Vector3D(Coordinate cord);
  double getLength();
  double getElementAt(int index);
  bool setLength(double);
  double *getVector();
  bool setVector(double x, double y, double z);
  bool setVector(Coordinate cord);
  double calcLength();
  void normalize();
  friend std::ostream& operator<<(std::ostream& os, Vector3D& a);
  static double dot(Vector3D a, Vector3D b) {
    double *pa = a.getVector();
    double *pb = b.getVector();

    return pa[0] * pb[0] + pa[1] * pb[1] + pa[2] * pb[2];
  }
  static Vector3D cross(Vector3D a, Vector3D b) {
    double cx = (a.getElementAt(1)*b.getElementAt(2)) - (a.getElementAt(2)*b.getElementAt(1));
    double cy = (a.getElementAt(2)*b.getElementAt(0)) - (a.getElementAt(0)*b.getElementAt(2));
    double cz = (a.getElementAt(0)*b.getElementAt(1)) - (a.getElementAt(1)*b.getElementAt(0));
    return Vector3D(cx,cy,cz);
  }

  Vector3D operator/(Vector3D right) {
    return Vector3D(vector[0] / right.getElementAt(0),
                  vector[1] / right.getElementAt(1),
                  vector[2] / right.getElementAt(2));
  }
  Vector3D operator-(Vector3D right) {
    return Vector3D(vector[0] - right.getElementAt(0),
                  vector[1] - right.getElementAt(1),
                  vector[2] - right.getElementAt(2));
  }

  bool operator==(Vector3D right){
    if(this->vector[0] == right.getElementAt(0) && this->vector[1] == right.getElementAt(1) && this->vector[2] == right.getElementAt(2)){
      return true;
    }
    return false;
  }

  Vector3D operator*(double right) {
    return Vector3D(vector[0] * right, vector[1] * right, vector[2] * right);
  }
  Vector3D operator/(double right) {
    Vector3D v = Vector3D(vector[0] / right, vector[1] / right, vector[2] / right);
    return v;
  }
  Vector3D operator+(double right){
    Vector3D v = Vector3D(vector[0] + right, vector[1] + right, vector[2] + right);
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

class Vector4D {
public:
  Vector4D();
  Vector4D(double x, double y, double z);
  Vector4D(Coordinate cord);
  Vector4D(Vector3D v3d);
  Coordinate toCoord();
  double getLength();
  double getElementAt(int index);
  bool setLength(double);
  double *getVector();
  bool setVector(double x, double y, double z,double h);
  bool setVector(Coordinate cord);
  double calcLength();
  void normalize();
  friend std::ostream& operator<<(std::ostream& os, Vector4D& a);
  static Vector4D cross(Vector4D a, Vector4D b) {
    double cx = (a.getElementAt(1)*b.getElementAt(2)) - (a.getElementAt(2)*b.getElementAt(1));
    double cy = (a.getElementAt(2)*b.getElementAt(0)) - (a.getElementAt(0)*b.getElementAt(2));
    double cz = (a.getElementAt(0)*b.getElementAt(1)) - (a.getElementAt(1)*b.getElementAt(0));
    return Vector4D(cx,cy,cz);
  }
  static double dot(Vector4D a, Vector4D b) {
    double *pa = a.getVector();
    double *pb = b.getVector();

    return pa[0] * pb[0] + pa[1] * pb[1] + pa[2] * pb[2];
  }

  Vector4D operator/(Vector4D right) {
    return Vector4D(vector[0] / right.getElementAt(0),
                  vector[1] / right.getElementAt(1),
                  vector[2] / right.getElementAt(2));
  }
  Vector4D operator-(Vector4D right) {
    return Vector4D(vector[0] - right.getElementAt(0),
                  vector[1] - right.getElementAt(1),
                  vector[2] - right.getElementAt(2));
  }

  bool operator==(Vector4D right){
    if(this->vector[0] == right.getElementAt(0) && this->vector[1] == right.getElementAt(1) && this->vector[2] == right.getElementAt(2) && this->vector[3] == right.getElementAt(3)){
      return true;
    }
    return false;
  }

  Vector4D operator*(double right) {
    return Vector4D(vector[0] * right, vector[1] * right, vector[2] * right);
  }
  Vector4D operator/(double right) {
    Vector4D v = Vector4D(vector[0] / right, vector[1] / right, vector[2] / right);
    return v;
  }
  Vector4D operator+(double right){
    Vector4D v = Vector4D(vector[0] + right, vector[1] + right, vector[2] + right);
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
  double vector[4];
  double lenght;
  int maxIndex;
};

#endif