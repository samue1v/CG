#ifndef SHAPES_H
#define SHAPES_H
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include "../DataStructures/Matrix.h"
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
  virtual Vector computeNormal(Coordinate P, Vector D) = 0;
  virtual double IntersectRay(Coordinate O, Vector D,double, double) = 0;
};

class Sphere : public Shape3D {
private:
	AmbientLight l;
  double radius;
  Coordinate center;

public:
  Sphere(Coordinate center, double radius, Material *material);
  Material *getMaterial();
  bool setMaterial(Material *material);
  bool setRadius(double newRadius);
  double getRadius();
  bool setCenter(Coordinate newCenter);
  Coordinate getCenter();
  Vector computeNormal(Coordinate P,Vector D);
  double IntersectRay(Coordinate O, Vector D,double, double);
};

class Plane : public Shape3D {
private:
  Vector normal;
  Coordinate planePoint;

public:
  Plane();
  Plane(Coordinate planePoint, Vector normal, Material * material);
  Material *getMaterial();
  Vector computeNormal(Coordinate P,Vector D);
  double IntersectRay(Coordinate O, Vector D,double, double);
  Coordinate getplanePoint();
  bool setplanePoint(Coordinate newplanePoint);
  Vector getNormal();
  bool setNormal(Vector newNormal);
};

class Cylinder : public Shape3D{
  private:
  Coordinate baseCenter;
  Coordinate topCenter;
  IntersectFace intersectSurf;
  Vector axis;
  Plane topLid;
  Plane baseLid;

  double height;
  double radius;
  Matrix<double,3,3> * M;
  public:
  Cylinder();
  Cylinder(Coordinate, Vector, double, double,Material*);
  Material *getMaterial();
  Vector computeNormal(Coordinate P,Vector D);
  double IntersectRay(Coordinate O, Vector D,double, double);

};

class Cone : public Shape3D{
  private:
  Coordinate baseCenter;
  Coordinate vertex;
  IntersectFace intersectSurf;
  Vector axis;
  Plane baseLid;
  double radius;
  double cosTeta;
  double height;
  double baseRadius;
  public:
  Cone();
  Cone(Coordinate, Vector, double, double,Material*);
  Material *getMaterial();
  Vector computeNormal(Coordinate P,Vector D);
  double IntersectRay(Coordinate O, Vector D,double, double);
};

#endif