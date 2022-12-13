#ifndef LIGHT_H
#define LIGHT_H

#include "../DataStructures/Coordinate.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Matrix.h"
#include "../Object_/Material.h"
#include "Intensity.h"
#include <string>

class Light {
public:
  virtual Intensity getIntensity() = 0;
  virtual bool setIntensity(Intensity) = 0;
  virtual Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *) = 0;
  virtual Vector3D calcDirection(Coordinate o) = 0;
  virtual Vector3D getReference() = 0;
  virtual std::string getName() = 0;
  virtual void applyViewTransform(Matrix<double,4,4> transformMatrix) = 0;
  Light();
protected:
  Intensity intensity;
  std::string name;


  //Intensity intensity = Intensity(1.0, 1.0, 1.0);
};

class AmbientLight : public Light {
public:
  AmbientLight();
  AmbientLight(Intensity intensity,std::string name);
  Intensity getIntensity();
  bool setIntensity(Intensity newIntensity);
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *);
  Vector3D calcDirection(Coordinate o);
  Vector3D getReference();
  void applyViewTransform(Matrix<double,4,4> transformMatrix);
  std::string getName();

private:

};

class DirectionalLight : public Light {
public:
  DirectionalLight();
  DirectionalLight(Intensity intensity, Vector3D direction,std::string name);
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *);
  Vector3D getDirection();
  bool setDirection(Vector3D);
  Intensity getIntensity();
  bool setIntensity(Intensity newIntensity);
  Vector3D calcDirection(Coordinate o);
  Vector3D getReference();
  void applyViewTransform(Matrix<double,4,4> transformMatrix);
  std::string getName();

private:
  Vector3D direction;
};

class PointLight : public Light {
public:
  PointLight();
  PointLight(Intensity intensity, Coordinate position,std::string name);
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *);
  Coordinate getPosition();
  bool setPosition(Coordinate);
  Intensity getIntensity();
  bool setIntensity(Intensity newIntensity);
  Vector3D calcDirection(Coordinate o);
  Vector3D getReference();
  void applyViewTransform(Matrix<double,4,4> transformMatrix);
  std::string getName();

private:
  Coordinate position;
};

class SpotLight : public Light{
  Intensity getIntensity() = 0;
  bool setIntensity(Intensity) = 0;
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *) = 0;
  Vector3D calcDirection(Coordinate o) = 0;
  Vector3D getReference() = 0;
  std::string getName() = 0;
  void applyViewTransform(Matrix<double,4,4> transformMatrix) = 0;
}

#endif