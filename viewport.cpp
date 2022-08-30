#include <stdio.h>
#include "ds.h"
#include "polygons.cpp"
#include "Scene.cpp"

class Viewport : Matrix{
  public:
    Coordinate canvasToViewport(int x, int y);
    Color TraceRay(Scene scene, Coordinate O, Matrix D, int t_min, int t_max);
  private:

};


Color Viewport::TraceRay(Scene scene, Coordinate O, Matrix D, int t_min, int t_max){
  long unsigned int closest_t = INF;
  Polygon closest_poly;
  
  for (Polygon polygon : scene.getPolygonArray(){
    //intersectRay tem que ser o método do poligono específico!
    long int t1, t2 = IntersectRay
  }

}