




#ifndef LIGHT_H
#define LIGHT_H

#include "../DataStructures/Coordinate.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Matrix.h"
#include "../Object_/Material.h"
#include "Intensity.h"

class Light {
public:
  virtual Intensity getIntensity() = 0;
  virtual bool setIntensity(Intensity) = 0;
  virtual Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *) = 0;
  virtual Vector3D calcDirection(Coordinate o) = 0;
  virtual Vector3D getReference() = 0;
  virtual void applyViewTransform(Matrix<double,4,4> transformMatrix) = 0;
  Light();


private:
  //Intensity intensity = Intensity(1.0, 1.0, 1.0);
};

class AmbientLight : public Light {
public:
  AmbientLight();
  AmbientLight(Intensity intensity);
  Intensity getIntensity();
  bool setIntensity(Intensity newIntensity);
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *);
  Vector3D calcDirection(Coordinate o);
  Vector3D getReference();
  void applyViewTransform(Matrix<double,4,4> transformMatrix);

private:
  Intensity intensity;
};

class DirectionalLight : public Light {
public:
  DirectionalLight();
  DirectionalLight(Intensity intensity, Vector3D direction);
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *);
  Vector3D getDirection();
  bool setDirection(Vector3D);
  Intensity getIntensity();
  bool setIntensity(Intensity newIntensity);
  Vector3D calcDirection(Coordinate o);
  Vector3D getReference();
  void applyViewTransform(Matrix<double,4,4> transformMatrix);

private:
  Vector3D direction;
  Intensity intensity;
};

class PointLight : public Light {
public:
  PointLight();
  PointLight(Intensity intensity, Coordinate position);
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *);
  Coordinate getPosition();
  bool setPosition(Coordinate);
  Intensity getIntensity();
  bool setIntensity(Intensity newIntensity);
  Vector3D calcDirection(Coordinate o);
  Vector3D getReference();
  void applyViewTransform(Matrix<double,4,4> transformMatrix);

private:
  Coordinate position;
  Intensity intensity;
};

#endif