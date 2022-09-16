#ifndef SHAPES_H
#define SHAPES_H
#include <math.h>
#include "Color.h"
#include "Pair.h"
#include "Coordinate.h"
#include "Vector.h"
#include "DataConsts.h"
#include "Reflect.h"
#include "Material.h"

class Shape3D {
public:
  Vector normal;
  Shape3D();
  virtual Material * getMaterial() = 0;
  virtual Coordinate getCenter()=0;
  virtual Pair<float> IntersectRay(Coordinate, Vector) = 0;
};


class Circle : public  Shape3D {
private:
  Material * material;
  float radius;
  Coordinate center;

public:
  Circle(Coordinate center, float radius, Material * material);
  Material * getMaterial();
  bool setMaterial(Material * material);
  bool setRadius(float newRadius);
  int getRadius();
  bool setCenter(Coordinate newCenter);
  Coordinate getCenter();
  Pair<float> IntersectRay(Coordinate O, Vector D);
};

#endif