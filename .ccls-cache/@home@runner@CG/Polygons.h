#ifndef POLYGONS_H
#define POLYGONS_H
#include <math.h>
#include "Color.h"
#include "Pair.h"
#include "Coordinate.h"
#include "Vector.h"
#include "DataConsts.h"

class Polygon {
public:
  Polygon();
};


class Circle : public Polygon {
private:
  Color color;
  float radius;
  Coordinate center;

public:
  Circle(Coordinate center, float radius, Color color);
  Color getColor();
  bool setColor(Color color);
  bool setRadius(float newRadius);
  int getRadius();
  bool setCenter(Coordinate newCenter);
  Coordinate getCenter();
  static Pair<float> IntersectRaySphere(Coordinate O, Vector D, Circle sphere){
    float r = sphere.getRadius();
    Vector c_minus_o = Vector(O - sphere.getCenter());
    float a = Vector::dot(D, D);
    float b = 2 * Vector::dot(c_minus_o, D);
    float c = Vector::dot(c_minus_o, c_minus_o) - r*r;
    
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
      return {INF,INF};
    }

    float t1 = (-b + sqrt(discriminant)) / (2*a);
    float t2 = (-b + sqrt(discriminant)) / (2*a);
    return {t1, t2};
  }
};

#endif