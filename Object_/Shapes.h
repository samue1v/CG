#ifndef SHAPES_H
#define SHAPES_H
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include "../DataStructures/Pair.h"
#include "../DataStructures/Vector.h"
#include "../Ilumination/Color.h"
#include "../Ilumination/Reflect.h"
#include "../Ilumination/Light.h"
#include "Material.h"

#include <math.h>

class Shape3D {
public:
  // Vector normal;
  Shape3D();
  Material *material;
  virtual Material *getMaterial() = 0;
  virtual Vector computeNormal(Coordinate P) = 0;
  virtual Pair<float> IntersectRay(Coordinate, Vector) = 0;
};

class Sphere : public Shape3D {
private:
	AmbientLight l;
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
  Vector computeNormal(Coordinate P);
  Pair<float> IntersectRay(Coordinate O, Vector D);
};

class Plane : public Shape3D {
private:
  Vector normal;
  Coordinate topLeftCorner;
  float height;
  float width;

public:
  Plane();
  Plane(Coordinate topLeftCorner, Vector normal, float width, float height, Material * material);
  Material *getMaterial();
  Vector computeNormal(Coordinate P);
  Pair<float> IntersectRay(Coordinate, Vector);
  Coordinate getTopLeftCorner();
  bool setTopLeftCorner(Coordinate newTopLeftCorner);
  float getHeight();
  bool setHeight(float newHeight);
  float getWidth();
  bool setWidth(float newWidth);
  Vector getNormal();
  bool setNormal(Vector newNormal);
};

#endif