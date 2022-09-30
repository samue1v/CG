#ifndef LIGHT_H
#define LIGHT_H

#include "../DataStructures/Coordinate.h"
#include "../DataStructures/Vector.h"
#include "../Object_/Material.h"
#include "Intensity.h"

class Light {
public:
  Light();
  virtual Intensity getIntensity() = 0;
  virtual bool setIntensity(Intensity) = 0;
  virtual Intensity calcIntensity(Coordinate, Vector, Vector,Material *) = 0;

private:
  Intensity intensity = Intensity(1.0, 1.0, 1.0);
};

class AmbientLight : public Light {
public:
  AmbientLight();
  AmbientLight(Intensity intensity);
  Intensity getIntensity();
  bool setIntensity(Intensity newIntensity);
  Intensity calcIntensity(Coordinate, Vector, Vector,Material *);

private:
  Intensity intensity;
};

class DirectionalLight : public Light {
public:
  DirectionalLight();
  DirectionalLight(Intensity intensity, Vector direction);
  Intensity calcIntensity(Coordinate, Vector, Vector,Material *);
  Vector getDirection();
  bool setDirection(Vector);
  Intensity getIntensity();
  bool setIntensity(Intensity newIntensity);

private:
  Vector direction;
  Intensity intensity;
};

class PointLight : public Light {
public:
  PointLight();
  PointLight(Intensity intensity, Coordinate position);
  Intensity calcIntensity(Coordinate, Vector, Vector,Material *);
  Coordinate getPosition();
  bool setPosition(Coordinate);
  Intensity getIntensity();
  bool setIntensity(Intensity newIntensity);

private:
  Coordinate position;
  Intensity intensity;
};

#endif