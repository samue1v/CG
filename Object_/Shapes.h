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
#include <string>
#include <math.h>

class Shape3D {
public:
  // Vector3D normal;
  Shape3D();
  virtual Texture * getTexture() = 0;
  virtual Color getTexel(Coordinate P,Coordinate O,Matrix<float,4,4> cameraToWorld) = 0;
  virtual bool setTexture(const std::string & filePath,SDL_Renderer * renderer) = 0;
  virtual Material *getMaterial() = 0;
  virtual Vector3D computeNormal(Coordinate P, Vector3D D) = 0;
  virtual float IntersectRay(Coordinate O, Vector3D D,float, float) = 0;
  virtual void transformView(Matrix<float,4,4> transformMatrix) = 0;
  virtual bool setTransform(Transformation * t) = 0;
  virtual std::string getName() = 0;
  Material *material;
  Texture * texture;
  std::string name;
};

class Sphere : public Shape3D {
private:
	AmbientLight l;
  float radius;
  Coordinate center;
  
  

public:
  Sphere();
  Sphere(Coordinate center, float radius, Material *material);
  Sphere(Coordinate center, float radius, Material *material,std::string name);
  Material *getMaterial();
  bool setMaterial(Material *material);
  bool setRadius(float newRadius);
  Color getTexel(Coordinate P,Coordinate O,Matrix<float,4,4> cameraToWorld);
  Texture * getTexture();
  void transformView(Matrix<float,4,4> transformMatrix);
  float getRadius();
  bool setCenter(Coordinate newCenter);
  bool setTexture(const std::string & filePath,SDL_Renderer * renderer);
  Coordinate getCenter();
  Vector3D computeNormal(Coordinate P,Vector3D D);
  float IntersectRay(Coordinate O, Vector3D D,float, float);
  bool setTransform(Transformation * t);
  std::string getName();
};

class Plane : public Shape3D {
private:
  Vector3D normal;
  Coordinate planePoint;

public:
  Plane();
  Plane(Coordinate planePoint, Vector3D normal, Material * material);
  Plane(Coordinate planePoint, Vector3D normal, Material * material,std::string name);
  void transformView(Matrix<float,4,4> transformMatrix);
  Material *getMaterial();
  Vector3D computeNormal(Coordinate P,Vector3D D);
  float IntersectRay(Coordinate O, Vector3D D,float, float);
  bool setTexture(const std::string & filePath,SDL_Renderer * renderer);
  Texture * getTexture();
  Color getTexel(Coordinate P,Coordinate O,Matrix<float,4,4> cameraToWorld);
  Coordinate getplanePoint();
  bool setplanePoint(Coordinate newplanePoint);
  Vector3D getNormal();
  bool setNormal(Vector3D newNormal);
  bool setTransform(Transformation * t);
  std::string getName();
};

class Cylinder : public Shape3D{
  private:
  Coordinate baseCenter;
  Coordinate topCenter;
  IntersectFace intersectSurf;
  Vector3D axis;
  Plane topLid;
  Plane baseLid;

  float height;
  float radius;
  Matrix<float,3,3> * M;
  public:
  Cylinder();
  Cylinder(Coordinate, Vector3D, float, float,Material*);
  Cylinder(Coordinate, Vector3D, float, float,Material*,std::string);
  Material *getMaterial();
  Vector3D computeNormal(Coordinate P,Vector3D D);
  void transformView(Matrix<float,4,4> transformMatrix);
  Texture * getTexture();
  Color getTexel(Coordinate P,Coordinate O,Matrix<float,4,4> cameraToWorld);
  float IntersectRay(Coordinate O, Vector3D D,float, float);
  bool setTexture(const std::string & filePath,SDL_Renderer * renderer);
  bool setTransform(Transformation * t);
  std::string getName();
};

class Cone : public Shape3D{
  private:
  Coordinate baseCenter;
  Coordinate vertex;
  IntersectFace intersectSurf;
  Vector3D axis;
  Plane baseLid;
  float radius;
  float cosTeta;
  float height;
  public:
  Cone();
  Cone(Coordinate, Vector3D, float, float,Material*);
  Cone(Coordinate, Vector3D, float, float,Material*,std::string);
  Material *getMaterial();
  Vector3D computeNormal(Coordinate P,Vector3D D);
  void transformView(Matrix<float,4,4> transformMatrix);
  Texture * getTexture();
  Color getTexel(Coordinate P,Coordinate O,Matrix<float,4,4> cameraToWorld);
  float IntersectRay(Coordinate O, Vector3D D,float, float);
  bool setTexture(const std::string & filePath,SDL_Renderer * renderer);
  bool setTransform(Transformation * t);
  std::string getName();
};

#endif