#ifndef SCENE_H
#define SCENE_H

#include "Shapes.h"
#include "Color.h"

class Scene {
public:
  Scene(int numShapes);
  Shape3D *getShapeAt(int index); // olhar depois
  bool setShapeAt(int index, Shape3D *shape);
  Shape3D *getShapesArray();
  int getNumberOfElements();
  bool setBackgroundColor(Color color);
  Color getBackgroundColor();

private:
  Color backgroud_color;
  int numShapes;
  Shape3D **elements;
};


#endif
