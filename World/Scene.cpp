#include "Scene.h"
#include "../DataStructures/DataConsts.h"
#include "../Ilumination/Light.h"
#include "../Object_/Shapes.h"
#include <iostream>
#include <stdio.h>

Scene::Scene(){}

Object *Scene::getObjectAt(int index) {
  return (this->elements).getElementAt(index);
}



bool Scene::setObject(Object *polygon){
  (this->elements).push(polygon);
  return true;
}


int Scene::getNumberOfElements() { return (this->elements).getSize(); }

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

bool Scene::setLight(Light * light){
  (this->lights).push(light);
  return true;
}

Light *Scene::getLightAt(int index){
  return (this->lights).getElementAt(index);
}

int Scene::getNumberOfLights() { return (this->lights).getSize(); }

Camera * Scene::getCamera(){
  return this->camera;
}

bool Scene::setCamera(Camera * newCamera){
  this->camera  = newCamera;
  return true;
}

void Scene::transformView(){
  for(int i = 0;i<this->elements.getSize();i++){
    this->elements.getElementAt(i)->applyViewTransform(this->camera->getWorldToCamera());
  }
  for(int j = 0;j<this->elements.getSize();j++){
    this->lights.getElementAt(j)->applyViewTransform(this->camera->getWorldToCamera());
  }
}