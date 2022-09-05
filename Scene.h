#ifndef SCENE_H
#define SCENE_H

#include "Polygons.h"
#include "Color.h"

class Scene {
public:
  Scene(int numPolygons);
  Polygon *getPolygonAt(int index); // olhar depois
  bool setPolygon(int index, Polygon *polygon);
  Polygon *getPolygonArray();
  int getNumberOfElements();
  bool setBackgroundColor(Color color);
  Color getBackgroundColor();

private:
  Color backgroud_color;
  int numPolygons;
  Polygon **elements;
};


#endif
