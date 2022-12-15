#ifndef LIGHT_H
#define LIGHT_H

#include "../DataStructures/Coordinate.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Matrix.h"
#include "../Object_/Material.h"
#include "Intensity.h"
#include <string>
#include <math.h> 

enum LightType{
  ambient = 0,
  directional = 1,
  point = 2,
  spot = 3
};

class Light {
public:
  Intensity getIntensity();
  std::string getName();
  bool getSwitchState();
  void flipSwitch();
  LightType getLightType();
  bool setIntensity(Intensity);
  virtual Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *) = 0;
  virtual Vector3D calcDirection(Coordinate o) = 0;
  virtual void applyViewTransform(Matrix<double,4,4> transformMatrix) = 0;
  virtual bool getAvaliable() = 0;
  Light();
protected:
  Intensity intensity;
  bool isAvaliable;
  bool isOn;
  LightType lightType;
  std::string name;


  //Intensity intensity = Intensity(1.0, 1.0, 1.0);
};

class AmbientLight : public Light {
public:
  AmbientLight();
  AmbientLight(Intensity intensity,std::string name);
  bool setIntensity(Intensity newIntensity);
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *);
  Vector3D calcDirection(Coordinate o);
  void applyViewTransform(Matrix<double,4,4> transformMatrix);
  bool getAvaliable();
private:

};

class DirectionalLight : public Light {
public:
  DirectionalLight();
  DirectionalLight(Intensity intensity, Vector3D direction,std::string name);
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *);
  Vector3D getDirection();
  bool setDirection(Vector3D);
  bool setIntensity(Intensity newIntensity);
  Vector3D calcDirection(Coordinate o);
  void applyViewTransform(Matrix<double,4,4> transformMatrix);
  bool getAvaliable();
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
  bool setIntensity(Intensity newIntensity);
  Vector3D calcDirection(Coordinate o);
  void applyViewTransform(Matrix<double,4,4> transformMatrix);
  bool getAvaliable();
private:
  Coordinate position;
};

class SpotLight : public Light{
public:
  SpotLight();
  SpotLight(Intensity intensity, Coordinate position, Vector3D direction, double angle,std::string name);
  Intensity getIntensity();
  bool setIntensity(Intensity);
  Intensity calcIntensity(Coordinate, Vector3D, Vector3D,Material *);
  Vector3D calcDirection(Coordinate P);
  std::string getName();
  void applyViewTransform(Matrix<double,4,4> transformMatrix);
  bool getAvaliable();
private:
  double angle;
  Coordinate position;
  Vector3D direction;

};

#endif