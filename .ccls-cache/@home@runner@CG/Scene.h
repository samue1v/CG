#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "Color.h"
#include "Light.h"

class Scene {
public:
  Scene(int numObjects,int numLights);
  Object *getObjectAt(int index); // olhar depois
  bool setObjectAt(int index, Object *obj);
  Object *getObjectsArray();
  int getNumberOfElements();
  Light * getLightAt(int index);
  //bool setLight(Light * l);
  int getNumberOfLights();
  bool setLightAt(int index,Light * l);
  bool setBackgroundColor(Color color);
  Color getBackgroundColor();

private:
  Color background_color;
  int numObjects;
  int numLights;
  Object **elements;
  Light **lights;
};


#endif
