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
  Coordinate canvasToViewport(double x, double y);

  static Intensity TraceRay(Scene *scene, Coordinate O, Vector D, double t_min,
                            double t_max) {
    //double change
    double closest_t = INF;
    Shape3D *closestShape = nullptr;
    for (int i = 0; i < scene->getNumberOfElements(); i++) {
      Object *object = scene->getObjectAt(i);
      for (int j = 0; j < object->getShapeCount(); j++) {
        Shape3D *shape = object->getShapeAt(j);
        double t = shape->IntersectRay(O, D,t_min,t_max);
        if (t >= t_min && t <= t_max && t < closest_t) {
          closest_t = t;
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
      Vector p_lightDir = scene->getLightAt(l)->calcDirection(P);
      double p_lightDirLength = p_lightDir.getLength();
      if(!Space3D::isOfuscated(P,p_lightDir,scene,closestShape,p_lightDirLength) || dynamic_cast<AmbientLight*>(scene->getLightAt(l))){
        i = i + scene->getLightAt(l)->calcIntensity(P, N, V * -1, closestShape->getMaterial());
      }
    }

		if(i.getBlue()>1 || i.getRed()>1 || i.getGreen()>1){
			i = i.normalize();
		}
    return i;
  }

  static bool isOfuscated(Coordinate O,Vector D,Scene* scene,Shape3D * closestShape,double maxLength){
      D.normalize();
     for (int i = 0; i < scene->getNumberOfElements(); i++) {
      Object *object = scene->getObjectAt(i);
      for (int j = 0; j < object->getShapeCount(); j++) {

        Shape3D *shape = object->getShapeAt(j);
        double t = shape->IntersectRay(O, D,1,INF);
        if(t>=1 && t<=maxLength){
          return true;

        }
      }
    }
    return false;
  }

private:
};

#endif