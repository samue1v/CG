#include "Scene.h"
#include "../DataStructures/DataConsts.h"
#include "../Ilumination/Light.h"
#include "../Object_/Shapes.h"
#include <iostream>
#include <stdio.h>

Scene::Scene(){
  bgIntensity = Intensity(0.53, 0.81, 0.92);
  naturalColor = Color(255, 255, 255);
}

Object *Scene::getObjectAt(int index) {
  return (this->elements).getElementAt(index);
}



bool Scene::setObject(Object *polygon){
  (this->elements).push(polygon);
  return true;
}


int Scene::getNumberOfElements() { return (this->elements).getSize(); }


Intensity Scene::getBackgroundIntensity() { return this->bgIntensity; }

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

void Scene::transformWorldToCamera(){
  for(int i = 0;i<this->elements.getSize();i++){
    this->elements.getElementAt(i)->applyViewTransform(this->camera->getWorldToCamera());
  }
  for(int j = 0;j<this->lights.getSize();j++){
    this->lights.getElementAt(j)->applyViewTransform(this->camera->getWorldToCamera());
  }
}

void Scene::transformCameraToWorld(){
  for(int i = 0;i<this->elements.getSize();i++){
    this->elements.getElementAt(i)->applyViewTransform(this->camera->getCameraToWorld());
  }
  for(int j = 0;j<this->lights.getSize();j++){
    this->lights.getElementAt(j)->applyViewTransform(this->camera->getCameraToWorld());
  }
}

Intensity Scene::getBgIntensity(){
  return bgIntensity;
}

Color Scene::getNaturalColor(){
  return naturalColor;
}
