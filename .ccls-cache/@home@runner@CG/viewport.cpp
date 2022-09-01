#include "Scene.cpp"
#include "ds.h"
#include <stdio.h>

class Viewport : Matrix {
public:
  Coordinate canvasToViewport(int x, int y);
  Color TraceRay(Scene scene, Coordinate O, Vector D, int t_min, int t_max);
  // private:
};

Color Viewport::TraceRay(Scene scene, Coordinate O, Vector D, int t_min,
                         int t_max) {
  long unsigned int closest_t = INF;
  Circle *closest_poly;

  for (int i = 0; i < scene.getNumberOfElements(); i++) {
    // intersectRay tem que ser o método do poligono específico!
    Circle *sphere = (Circle *)scene.getPolygonAt(i);
    Pair<int> pair = Circle::IntersectRaySphere(O, D, sphere);
    int t1 = pair.left;
    int t2 = pair.right;
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
    return scene.getBackgroundColor();
  }
  return closest_poly->getColor();
}