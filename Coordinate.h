#ifndef COORDINATE_H
#define COORDINATE_H
#include "Vector.h"
/*
Operadores que temos:
Ponto - Ponto -> Ponto
Ponto + Ponto -> Ponto
Ponto + Vetor -> Ponto
Ponto - Vetor -> Ponto
*/
struct Coordinate {
  float x;
  float y;
  float z;
  Coordinate();
  Coordinate(float x, float y, float z);
  static float dot(Coordinate a, Coordinate b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }
//pontos:
  Coordinate operator+(Coordinate right) {
    return Coordinate(x + right.x, y + right.y, z + right.z);
  }
  Coordinate operator-(Coordinate right) {
    return Coordinate(x - right.x, y - right.y, z - right.z);
  }
};
#endif