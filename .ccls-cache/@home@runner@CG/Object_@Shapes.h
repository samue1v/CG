#ifndef SHAPES_H
#define SHAPES_H
#include "../Ilumination/Color.h"
#include "../Ilumination/Reflect.h"
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include "../DataStructures/Pair.h"
#include "../DataStructures/Vector.h"
#include "Material.h"



#include <math.h>

class Shape3D {
public:
  Vector normal;
  Shape3D();
  Material *material;
  virtual Material *getMaterial() = 0;
  virtual Coordinate getCenter() = 0;
  virtual Pair<float> IntersectRay(Coordinate, Vector) = 0;
};

class Sphere : public Shape3D {
private:
  float radius;
  Coordinate center;

public:
  Sphere(Coordinate center, float radius, Material *material);
  Material *getMaterial();
  bool setMaterial(Material *material);
  bool setRadius(float newRadius);
  int getRadius();
  bool setCenter(Coordinate newCenter);
  Coordinate getCenter();
  Pair<float> IntersectRay(Coordinate O, Vector D);
};

#endif