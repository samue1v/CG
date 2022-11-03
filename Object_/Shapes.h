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
  // Vector3D normal;
  Shape3D();
  Material *material;
  virtual Material *getMaterial() = 0;
  virtual Vector3D computeNormal(Coordinate P, Vector3D D) = 0;
  virtual double IntersectRay(Coordinate O, Vector3D D,double, double) = 0;
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
  Vector3D computeNormal(Coordinate P,Vector3D D);
  double IntersectRay(Coordinate O, Vector3D D,double, double);
};

class Plane : public Shape3D {
private:
  Vector3D normal;
  Coordinate planePoint;

public:
  Plane();
  Plane(Coordinate planePoint, Vector3D normal, Material * material);
  Material *getMaterial();
  Vector3D computeNormal(Coordinate P,Vector3D D);
  double IntersectRay(Coordinate O, Vector3D D,double, double);
  Coordinate getplanePoint();
  bool setplanePoint(Coordinate newplanePoint);
  Vector3D getNormal();
  bool setNormal(Vector3D newNormal);
};

class Cylinder : public Shape3D{
  private:
  Coordinate baseCenter;
  Coordinate topCenter;
  IntersectFace intersectSurf;
  Vector3D axis;
  Plane topLid;
  Plane baseLid;

  double height;
  double radius;
  Matrix<double,3,3> * M;
  public:
  Cylinder();
  Cylinder(Coordinate, Vector3D, double, double,Material*);
  Material *getMaterial();
  Vector3D computeNormal(Coordinate P,Vector3D D);
  double IntersectRay(Coordinate O, Vector3D D,double, double);

};

class Cone : public Shape3D{
  private:
  Coordinate baseCenter;
  Coordinate vertex;
  IntersectFace intersectSurf;
  Vector3D axis;
  Plane baseLid;
  double radius;
  double cosTeta;
  double height;
  public:
  Cone();
  Cone(Coordinate, Vector3D, double, double,Material*);
  Material *getMaterial();
  Vector3D computeNormal(Coordinate P,Vector3D D);
  double IntersectRay(Coordinate O, Vector3D D,double, double);
};

#endif