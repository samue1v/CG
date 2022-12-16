#ifndef SPACE3D_H
#define SPACE3D_H
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/Matrix.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Triple.h"
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

  static Triple<Object *,Intensity,Color> TraceRay(Scene *scene, Coordinate O, Vector3D D, double t_min,
                            double t_max) {
    double closest_t = INF;
    double closest_shape_t = INF;
    double closest_mesh_t = INF;
    Color texel = Color();
    Shape3D *closestShape = nullptr;
    Mesh * closestMesh = nullptr;
    Object * closestObject = nullptr;
    Triple<Object *,Intensity,Color> hitData;
    for (int i = 0; i < scene->getNumberOfElements(); i++) {
      Object *object = scene->getObjectAt(i);
      for (int j = 0; j < object->getShapeCount(); j++) {
        Shape3D *shape = object->getShapeAt(j);
        double t = shape->IntersectRay(O, D,t_min,t_max);
        if (t >= t_min && t <= t_max && t < closest_shape_t && t<closest_mesh_t) {
          closest_shape_t = t;
          closestShape = shape;
          closestObject = object;
        }
      }
      for(int k = 0;k<object->getMeshCount();k++){
        Mesh * mesh = object->getMeshAt(k);
        double t = mesh->IntersectRay(O,D,t_min,t_max);
        if (t >= t_min && t <= t_max && t < closest_mesh_t && t< closest_shape_t) {
          closest_mesh_t = t;
          closestMesh = mesh;
          closestObject = object;
        }
      }

    }
    
    if (!closestShape && !closestMesh) {
      
      hitData.left = nullptr;
      hitData.middle = scene->getBackgroundIntensity();
      hitData.right = Color();
      return hitData;
      
    }
    
    
    if(closest_mesh_t<closest_shape_t && closest_mesh_t<closest_t){
      closest_t = closest_mesh_t;
    }
    else if(closest_shape_t<closest_mesh_t && closest_shape_t<closest_t){
      closest_t = closest_shape_t;
    }
    
    
    Intensity i = Intensity(); // 0,0,0
    Coordinate P = (D * closest_t) + O;
    Vector3D N; 
    Vector3D V;
    V = D;
    V.normalize();
    if(closest_shape_t<closest_mesh_t){
      N = closestShape->computeNormal(P,D); 
      N.normalize();
      texel =  closestShape->getTexel(P,O,scene->getCamera()->getCameraToWorld());
      for (int l = 0; l < scene->getNumberOfLights(); l++) {
        Light * curLight = scene->getLightAt(l);
        LightType lightType = curLight->getLightType();
        
        if(lightType==ambient){
          if(curLight->getSwitchState()){
            i = i + curLight->calcIntensity(P, N, V * -1, closestShape->getMaterial());
          }
        }
        else if(lightType==point){
          Vector3D p_lightDir = curLight->calcDirection(P);
          double p_lightDirLength = p_lightDir.getLength();
          if(curLight->getSwitchState() && !Space3D::isOfuscated(P,p_lightDir,scene,p_lightDirLength)){
            i = i + curLight->calcIntensity(P, N, V * -1, closestShape->getMaterial());
          }
        }
        else if(lightType==directional){
          Vector3D p_lightDir = curLight->calcDirection(P);
          double p_lightDirLength = 100000;
          if(curLight->getSwitchState() && curLight->getAvaliable() && !Space3D::isOfuscated(P,p_lightDir,scene,p_lightDirLength)){
            i = i + curLight->calcIntensity(P, N, V * -1, closestShape->getMaterial());
          }
        }
        else if(lightType==spot){
          Vector3D p_lightDir = curLight->calcDirection(P);
          double p_lightDirLength = p_lightDir.getLength();
          if(curLight->getSwitchState() && curLight->getAvaliable() && !Space3D::isOfuscated(P,p_lightDir,scene,p_lightDirLength)){
            i = i + curLight->calcIntensity(P, N, V * -1, closestShape->getMaterial());
          }
        }
      }
    }
    else{
      N = closestMesh->computeNormal(); 
      N.normalize();
      texel =  closestMesh->getTexel(P,O,scene->getCamera()->getCameraToWorld());
      for (int l = 0; l < scene->getNumberOfLights(); l++) {
        Light * curLight = scene->getLightAt(l);
        LightType lightType = curLight->getLightType();
        
        if(lightType==ambient){
          if(curLight->getSwitchState()){
            i = i + curLight->calcIntensity(P, N, V * -1, closestMesh->getMaterial());
          }
        }
        else if(lightType==point){
          Vector3D p_lightDir = curLight->calcDirection(P);
          double p_lightDirLength = p_lightDir.getLength();
          if(curLight->getSwitchState() && !Space3D::isOfuscated(P,p_lightDir,scene,p_lightDirLength)){
            i = i + curLight->calcIntensity(P, N, V * -1, closestMesh->getMaterial());
          }
        }
        else if(lightType==directional){
          Vector3D p_lightDir = curLight->calcDirection(P);
          double p_lightDirLength = 100000;
          if(curLight->getSwitchState() && curLight->getAvaliable() && !Space3D::isOfuscated(P,p_lightDir,scene,p_lightDirLength)){
            i = i + curLight->calcIntensity(P, N, V * -1, closestMesh->getMaterial());
          }
        }
        else if(lightType==spot){
          Vector3D p_lightDir = curLight->calcDirection(P);
          double p_lightDirLength = p_lightDir.getLength();
          if(curLight->getSwitchState() && curLight->getAvaliable() && !Space3D::isOfuscated(P,p_lightDir,scene,p_lightDirLength)){
            i = i + curLight->calcIntensity(P, N, V * -1, closestMesh->getMaterial());
          }
        }
      }
    }
    //std::cout<<i;
		if(i.getBlue()>1 || i.getRed()>1 || i.getGreen()>1){
			i = i.normalize();
		}
    //std::cout<<i;

    hitData.left = closestObject;
    hitData.middle= i;
    hitData.right = texel;
    return hitData;
  }

  static bool isOfuscated(Coordinate O,Vector3D D,Scene* scene,double maxLength){
    D.normalize();
     for (int i = 0; i < scene->getNumberOfElements(); i++) {
      Object *object = scene->getObjectAt(i);
      for (int j = 0; j < object->getShapeCount(); j++) {
        Shape3D *shape = object->getShapeAt(j);
        double t = shape->IntersectRay(O, D,1,maxLength);
        //std::cout<<t<<"\n";
        //std::cout<<D<<"\n";
        if(t>=1 && t<=maxLength){
          return true;
        }
      }
      for (int k = 0; k < object->getMeshCount(); k++) {

        Mesh *mesh = object->getMeshAt(k);
        double t = mesh->IntersectRay(O, D,1,maxLength);
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