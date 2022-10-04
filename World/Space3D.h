#ifndef SPACE3D_H
#define SPACE3D_H
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/Matrix.h"
#include "../DataStructures/Vector.h"
#include "../Ilumination/Color.h"
#include "../Ilumination/Intensity.h"
#include "../Ilumination/Light.h"
#include "../Ilumination/Reflect.h"
#include "Scene.h"
#include <iostream>
#include <stdio.h>

class Space3D {
public:
  Coordinate canvasToViewport(float x, float y);
  static Intensity TraceRay(Scene *scene, Coordinate O, Vector D, int t_min,
                            int t_max) {
    //float change
    float closest_t = INF;
    Shape3D *closestShape = nullptr;
    for (int i = 0; i < scene->getNumberOfElements(); i++) {
      Object *object = scene->getObjectAt(i);
      for (int j = 0; j < object->getShapeCount(); j++) {
        Shape3D *shape = object->getShapeAt(j);
        Pair<float> pair = shape->IntersectRay(O, D);
        float t1 = pair.left;
        float t2 = pair.right;
        if (t1 >= t_min && t1 < t_max && t1 < closest_t) {
          closest_t = t1;
          closestShape = shape;
        }
        if (t2 >= t_min && t2 < t_max && t2 < closest_t) {
          closest_t = t2;
          closestShape = shape;
        }
      }
    }
    if (!closestShape) {
      return scene->getBackgroundCoefs();
    }
    Intensity i = Intensity(); // 0,0,0
    Coordinate P = (D * closest_t) + O;
    Vector N = closestShape->computeNormal(P);
    Vector V = D;
    V.normalize();
    N.normalize();
    for (int l = 0; l < scene->getNumberOfLights(); l++) {
      i = i + scene->getLightAt(l)->calcIntensity(P, N, V * -1,
                                                  closestShape->getMaterial());
    }
		if(i.getBlue()>1 || i.getRed()>1 || i.getGreen()>1){
			i = i.normalize();
		}
    return i;
  }

private:
};

#endif