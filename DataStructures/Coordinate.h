#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate {
  double x;
  double y;
  double z;
  Coordinate();
  Coordinate(double x, double y, double z);
  static double dot(Coordinate a, Coordinate b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }
//pontos:
  Coordinate operator+(Coordinate right) {
    return Coordinate(x + right.x, y + right.y, z + right.z);
  }
  Coordinate operator-(Coordinate right) {
    return Coordinate(x - right.x, y - right.y, z - right.z);
  }
  Coordinate operator*(double right) {
    return Coordinate(x * right, y * right, z * right);
  }
};
#endif