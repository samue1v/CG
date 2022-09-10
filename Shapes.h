#ifndef SHAPES_H
#define SHAPES_H
#include <math.h>
#include "Color.h"
#include "Pair.h"
#include "Coordinate.h"
#include "Vector.h"
#include "DataConsts.h"

class Shape3D {
public:
  Shape3D();
  virtual Color getColor() = 0;
  virtual Pair<float> IntersectRay(Coordinate, Vector) = 0;
};


class Circle : public  Shape3D {
private:
  Color color;
  float radius;
  Coordinate center;

public:
  Circle(Coordinate center, float radius, Color color);
  Color getColor();
  bool setColor(Color color);
  bool setRadius(float newRadius);
  int getRadius();
  bool setCenter(Coordinate newCenter);
  Coordinate getCenter();
  Pair<float> IntersectRay(Coordinate O, Vector D);
};

#endif