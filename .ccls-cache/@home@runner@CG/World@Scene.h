#ifndef SCENE_H
#define SCENE_H

#include "../Ilumination/Color.h"
#include "../Ilumination/Intensity.h"
#include "../Ilumination/Light.h"
#include "../Object_/Object.h"

class Scene {
public:
  Scene(int numObjects, int numLights);
  Object *getObjectAt(int index); // olhar depois
  bool setObjectAt(int index, Object *obj);
  Object *getObjectsArray();
  int getNumberOfElements();
  Light *getLightAt(int index);
  // bool setLight(Light * l);
  int getNumberOfLights();
  bool setLightAt(int index, Light *l);
  bool setBackgroundCoefs(Intensity coefs);
  Intensity getBackgroundCoefs();

private:
  Intensity background_coefs;
  int numObjects;
  int numLights;
  Object **elements;
  Light **lights;
};

#endif
