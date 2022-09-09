#include <stdio.h>
#include <iostream>
#include "DataConsts.h"
#include "Shapes.h"
#include "Scene.h"


Scene::Scene(int numShapes) : numShapes(numShapes),elements(new  Shape3D *[numShapes]){}
Shape3D *Scene::getShapeAt(int index) {
  Shape3D *p = (this->elements)[index]; 
  return p;
}
Shape3D *Scene::getShapesArray() {
  return *(this->elements);
}

bool Scene::setShapeAt(int index, Shape3D *polygon) {
  if (index >= numShapes || index < 0) {
    return false;
  }
  this->elements[index] = polygon;

  return true;
}

int Scene::getNumberOfElements() { return this->numShapes; }

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