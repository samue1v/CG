#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Scene.h"
#include "Coordinate.h"
#include "Vector.h"
#include "Matrix.h"
#include "Color.h"

template <typename T> class Viewport : Matrix<T> {
public:
  Coordinate canvasToViewport(float x, float y);
  static Color TraceRay(Scene *scene, Coordinate O, Vector D, int t_min, int t_max) {
    long unsigned int closest_t = INF;
    Circle *closest_poly;

    for (int i = 0; i < scene->getNumberOfElements(); i++) {
      Circle *sphere = (Circle *)scene->getPolygonAt(i);
      Pair<float> pair = Circle::IntersectRaySphere(O, D, *sphere); //melhor ser ponteiro pra circle ou nao?
      float t1 = pair.left;
      float t2 = pair.right;
      if (t1 >= t_min && t1 < t_max && t1 < closest_t) {
        closest_t = t1;
        closest_poly = sphere;
      }
      if (t2 >= t_min && t2 < t_max && t2 < closest_t) {
        closest_t = t2;
        closest_poly = sphere;
      }
    }
    if (closest_poly == NULL) {
      return scene->getBackgroundColor();
    }
    return closest_poly->getColor();
}
  // private:
};

#endif