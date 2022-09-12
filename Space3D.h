#ifndef SPACE3D_H
#define SPACE3D_H
#include <stdio.h>
#include <iostream>
#include "Scene.h"
#include "Coordinate.h"
#include "Vector.h"
#include "Matrix.h"
#include "Color.h"
#include "Light.h"

class Space3D{
public:
  Coordinate canvasToViewport(float x, float y);
  static Color TraceRay(Scene *scene, Coordinate O, Vector D, int t_min, int t_max) {
    long unsigned int closest_t = INF;
    Shape3D *closest_shape = nullptr;
    for(int i = 0; i < scene->getNumberOfElements(); i++) {
      Object *object = scene->getObjectAt(i);
      for(int j = 0;j<object->getShapeCount();j++){
        Shape3D *shape = object->getShapeAt(j);
        Pair<float> pair = shape->IntersectRay(O, D); 
        float t1 = pair.left;
        float t2 = pair.right;
        if (t1 >= t_min && t1 < t_max && t1 < closest_t) {
          closest_t = t1;
          closest_shape = shape;
        }
        if (t2 >= t_min && t2 < t_max && t2 < closest_t) {
          closest_t = t2;
          closest_shape = shape;
        }
      }
    }
    if (!closest_shape) {
      return scene->getBackgroundColor();
    }
    float i=0;
    for(int l=0;l<scene->getNumberOfLights();l++){
      i+= scene->getLightAt(l)->calcIntensity(O,D);
      std::cout<< scene->getLightAt(l)->getIntensity()<<"\n";
      exit(-1);
    }
    //std::cout << i<<"\n";
    return closest_shape->getColor()*i;
  }


    
  private:

};


#endif