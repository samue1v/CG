#ifndef SCENE_H
#define SCENE_H

#include "../Ilumination/Color.h"
#include "../Ilumination/Intensity.h"
#include "../Ilumination/Light.h"
#include "../Object_/Object.h"
#include "../Object_/Texture.h"
#include "../Camera/Camera.h"

class Scene {
public:
  Scene();
  Object *getObjectAt(int index);
  bool setObject(Object *obj);
  int getNumberOfElements();
  Light *getLightAt(int index);
  bool setLight(Light * l);
  int getNumberOfLights();
  Intensity getBackgroundCoefs();
  Camera * getCamera();
  bool setCamera(Camera * newCamera);
  void transformView();
  Intensity getBgIntensity();
  Color getNaturalColor();

private:
  Intensity bgIntensity;
  Color naturalColor;
  Camera * camera;
  Intensity background_coefs;
  Array<Object *> elements;
  Array<Light *> lights;
};

#endif
