#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "Color.h"

class Scene {
public:
  Scene(int numObjects);
  Object *getObjectAt(int index); // olhar depois
  bool setObjectAt(int index, Object *obj);
  Object *getObjectsArray();
  int getNumberOfElements();
  bool setBackgroundColor(Color color);
  Color getBackgroundColor();

private:
  Color background_color;
  int numObjects;
  Object **elements;
};


#endif
