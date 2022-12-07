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
#include "Transformation.h"
#include "Material.h"
#include "Texture.h"

#include <math.h>

class Shape3D {
public:
  // Vector3D normal;
  Shape3D();
  Material *material;
  Texture * texture;
  virtual Texture * getTexture() = 0;
  virtual Color getTexel(Coordinate P,Coordinate O,Matrix<double,4,4> cameraToWorld) = 0;
  virtual bool setTexture(const std::string & filePath,SDL_Renderer * renderer) = 0;
  virtual Material *getMaterial() = 0;
  virtual Vector3D computeNormal(Coordinate P, Vector3D D) = 0;
  virtual double IntersectRay(Coordinate O, Vector3D D,double, double) = 0;
  virtual void transformView(Matrix<double,4,4> transformMatrix) = 0;
  virtual bool setTransform(Transformation * t) = 0;
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
  Color getTexel(Coordinate P,Coordinate O,Matrix<double,4,4> cameraToWorld);
  Texture * getTexture();
  void transformView(Matrix<double,4,4> transformMatrix);
  double getRadius();
  bool setCenter(Coordinate newCenter);
  bool setTexture(const std::string & filePath,SDL_Renderer * renderer);
  Coordinate getCenter();
  Vector3D computeNormal(Coordinate P,Vector3D D);
  double IntersectRay(Coordinate O, Vector3D D,double, double);
  bool setTransform(Transformation * t);
};

class Plane : public Shape3D {
private:
  Vector3D normal;
  Coordinate planePoint;

public:
  Plane();
  Plane(Coordinate planePoint, Vector3D normal, Material * material);
  void transformView(Matrix<double,4,4> transformMatrix);
  Material *getMaterial();
  Vector3D computeNormal(Coordinate P,Vector3D D);
  double IntersectRay(Coordinate O, Vector3D D,double, double);
  bool setTexture(const std::string & filePath,SDL_Renderer * renderer);
  Texture * getTexture();
  Color getTexel(Coordinate P,Coordinate O,Matrix<double,4,4> cameraToWorld);
  Coordinate getplanePoint();
  bool setplanePoint(Coordinate newplanePoint);
  Vector3D getNormal();
  bool setNormal(Vector3D newNormal);
  bool setTransform(Transformation * t);
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
  void transformView(Matrix<double,4,4> transformMatrix);
  Texture * getTexture();
  Color getTexel(Coordinate P,Coordinate O,Matrix<double,4,4> cameraToWorld);
  double IntersectRay(Coordinate O, Vector3D D,double, double);
  bool setTexture(const std::string & filePath,SDL_Renderer * renderer);
  bool setTransform(Transformation * t);
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
  void transformView(Matrix<double,4,4> transformMatrix);
  Texture * getTexture();
  Color getTexel(Coordinate P,Coordinate O,Matrix<double,4,4> cameraToWorld);
  double IntersectRay(Coordinate O, Vector3D D,double, double);
  bool setTexture(const std::string & filePath,SDL_Renderer * renderer);
  bool setTransform(Transformation * t);
};

#endif