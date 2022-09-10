#include <stdio.h>
#include <iostream>
#include "DataConsts.h"
#include "Shapes.h"
#include "Scene.h"


Scene::Scene(int numObjects) : numObjects(numObjects),elements(new  Object *[numObjects]){}
Object *Scene::getObjectAt(int index) {
  Object *p = (this->elements)[index]; 
  return p;
}
Object *Scene::getObjectsArray() {
  return *(this->elements);
}

bool Scene::setObjectAt(int index, Object *polygon) {
  if (index >= numObjects || index < 0) {
    return false;
  }
  this->elements[index] = polygon;

  return true;
}

int Scene::getNumberOfElements() { return this->numObjects; }

bool Scene::setBackgroundColor(Color color) {
  if (color.red > COLOR_MAX || color.red < COLOR_MIN ||
      color.green > COLOR_MAX || color.green < COLOR_MIN ||
      color.blue < COLOR_MIN || color.blue > COLOR_MAX) {
    return false;
  }
  this->background_color = color;
  return true;
}
Color Scene::getBackgroundColor() { return this->background_color; }