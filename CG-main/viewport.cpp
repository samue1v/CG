#include <stdio.h>
#include "ds.h"
#include "polygons.cpp"

class Viewport : Matrix{
  public:
    Color TraceRay(Scene scene, coordinate O, Matrix D, int t_min, int t_max);
  private:

};


Color Viewport::TraceRay(Scene scene, coordinate O, Matrix D, int t_min, int t_max){
  long unsigned int closest_t = INF;
  Polygon closest_poly;
  
  for (Polygon polygon : scene.elements){
    //intersectRay tem que ser o método do poligono específico!
    long int t1, t2 = IntersectRay
  }

}