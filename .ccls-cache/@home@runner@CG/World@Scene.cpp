#include "Scene.h"
#include "../DataStructures/DataConsts.h"
#include "../Ilumination/Light.h"
#include "../Object_/Shapes.h"
#include <iostream>
#include <stdio.h>

Scene::Scene(int numObjects, int numLights)
    : numObjects(numObjects), numLights(numLights),
      elements(new Object *[numObjects]), lights(new Light *[numLights]) {}
Object *Scene::getObjectAt(int index) {
  Object *p = (this->elements)[index];
  return p;
}
Object *Scene::getObjectsArray() { return *(this->elements); }

bool Scene::setObjectAt(int index, Object *polygon) {
  if (index >= numObjects || index < 0) {
    return false;
  }
  this->elements[index] = polygon;

  return true;
}

int Scene::getNumberOfElements() { return this->numObjects; }

bool Scene::setBackgroundCoefs(Intensity coefs) {
  if (coefs.getRed() > INTENSITY_MAX || coefs.getRed() < INTENSITY_MIN ||
      coefs.getGreen() > INTENSITY_MAX || coefs.getGreen() < INTENSITY_MIN ||
      coefs.getBlue() > INTENSITY_MAX || coefs.getBlue() < INTENSITY_MIN) {
    return false;
  }
  this->background_coefs = coefs;
  return true;
}
Intensity Scene::getBackgroundCoefs() { return this->background_coefs; }

bool Scene::setLightAt(int index, Light *light) {
  if (index >= numLights || index < 0) {
    return false;
  }
  this->lights[index] = light;

  return true;
}

Light *Scene::getLightAt(int index) {
  if (index >= numLights || index < 0) {
    return nullptr;
  }
  return lights[index];
}

int Scene::getNumberOfLights() { return this->numLights; }