#include "ds.h"
#include "polygons.cpp"
#include <stdio.h>

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
  Polygon *elements;
};

Scene::Scene(int numPolygons) {
  Polygon *p;
  Polygon *polygonsArray[numPolygons];
  this->numPolygons = numPolygons;
  this->elements = *polygonsArray;
}
Polygon *Scene::getPolygonAt(int index) {
  Polygon *p = &(this->elements)[index]; // ver qual a maneira correta
  return p;
}
Polygon *Scene::getPolygonArray() {
  Polygon *p = this->elements;
  return p;
}

bool Scene::setPolygon(int index, Polygon *polygon) {
  if (index >= numPolygons || index < 0) {
    return false;
  }
  this->elements[index] = *(polygon);
  return true;
}

int Scene::getNumberOfElements() { return this->numPolygons; }

bool Scene::setBackgroundColor(Color color) {
  if (color.red > COLOR_MAX || color.red < COLOR_MIN ||
      color.green > COLOR_MAX || color.green < COLOR_MIN ||
      color.blue < COLOR_MIN || color.blue > COLOR_MAX) {
    return false;
  }
  this->backgroud_color = color;
  return true;
}
Color Scene::getBackgroundColor() { return this->backgroud_color; }