/*
Lembrar de olhar o calculo da normal da malha, lembra da ordem g o f
lembra que eu mudei canvas distance pra ser positivo, logo no loop principal deve-se mudar
para -canvas_distance
*/

#include "../Canvas_/Canvas.h"
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include "../DataStructures/Matrix.h"
#include "../DataStructures/Vector.h"
#include "../Ilumination/Color.h"
#include "../Ilumination/Intensity.h"
#include "../Ilumination/Light.h"
#include "../Ilumination/Reflect.h"
#include "../Object_/Object.h"
#include "../Object_/Shapes.h"
#include "../Object_/Transformation.h"
#include "../World/Scene.h"
#include "../World/Space3D.h"
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>

template<int l,int k>
bool writePPM(Canvas<l,k> *canvas) {
  std::ofstream myfile;
  Matrix<Color,l,k> *m = canvas->getCanvas();
  myfile.open("image.ppm");
  myfile << "P3\n";
  myfile << canvas->getNumberLines() << ' ' << canvas->getNumberColumns()
         << '\n';
  myfile << 255 << '\n';
  unsigned char RGBarray[6];
  RGBarray[1] = ' ';
  RGBarray[3] = ' ';
  RGBarray[5] = ' ';

  for (int i = 0; i < canvas->getNumberLines(); i++) {
    for (int j = 0; j < canvas->getNumberColumns(); j++) {
      // std::cout << (int)m->getVal(i, j).red <<"\n";
      myfile << ' ' << (int)m->getVal(i, j).red << ' '
             << (int)m->getVal(i, j).green << ' ' << (int)m->getVal(i, j).blue
             << ' ';
    }
    myfile << '\n';
  }
  return true;
}

template<int l,int k>
bool SDLdraw(Canvas<l,k> *canvas){
  Matrix<Color,l,k> *m = canvas->getCanvas();
  SDL_Window * window =nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(500,500, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);
  for(int i =0;i<l;i++){
    for(int j = 0;j>k;j++){
        SDL_SetRenderDrawColor(renderer,(int)m->getVal(i, j).red,(int)m->getVal(i, j).green,(int)m->getVal(i, j).blue,255);
        SDL_RenderDrawPoint(renderer,i,j);

    }
  }
  SDL_RenderPresent(renderer);
  SDL_Delay(10000);
  return true;
}

int main() {

  Coordinate O = Coordinate(0, 0, 0);
  Coordinate Po = Coordinate(0,0,250);
  Intensity bgIntensity = Intensity(0, 0, 0);
  Color whiteColor = Color(255, 255, 255);
  double wj = 60;
  double hj = 60;

  const int nLines = 500;
  const int nColumns = 500;
  double dx = wj / nColumns;
  double dy = hj / nLines;
  double canvasDistance = 220;
  double sphereDistance = 60;
  // double sphere_distance = 100;
  // inicialização da cena e da esfera
  double radius = 40;

  Coordinate center = Coordinate(0, 0, -(sphereDistance + radius));

  //Materials
  Rubber *rubber = new Rubber();
  Metal *metal = new Metal();
  Plastic *plastic = new Plastic();
  Cooper *cooper = new Cooper();
  Marble *marble = new Marble();

  //Sphere
  Sphere *circle = new Sphere(center, radius, rubber);

  //Cylinder
  Vector3D cylinderAxis = Vector3D(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
  Cylinder * cylinder = new Cylinder(center,cylinderAxis,radius/3,3*radius,cooper);
  Coordinate cylinderTop = (cylinderAxis*3*radius)+center;
  
  //Cone
  double coneRadius = 1.5*radius;
  //Cone * cone = new Cone(cylinderTop,cylinderAxis,coneRadius,coneRadius/3,marble);
  Cone * cone = new Cone(center,cylinderAxis*-1,coneRadius,coneRadius/3,marble);
  //Cone * cone = new Cone(Coordinate(0,0,-100),Vector3D(-1,0,0),radius,radius*2,marble);

  //Planes
	Coordinate floorPoint = Coordinate(0,-radius,0);
	Vector3D floorNormal = Vector3D(0,1,0);
  Coordinate backPoint = Coordinate(0,0,-200);
	Vector3D backNormal = Vector3D(0,0,1);
	Plane *floorPlane = new Plane(floorPoint, floorNormal, metal);
	Plane *backPlane = new Plane(backPoint, backNormal, plastic);

  //Meshes
  std::string path = "../MeshFiles/teste1obj.obj";
  Mesh * mesh = new Mesh(path,rubber);
  //mesh->setTransform(new Scale(25,20,20));
  mesh->setTransform(new RotateY(45));
  mesh->setTransform(new RotateX(45));
  //mesh->setTransform(new RotateZ(45));
  //mesh->setTransform(new Translate(10,0,-30));
  //mesh->setTransform(new ShearYX(30));
  
  //mesh->applyTransform();

  //Object
  char name[] = "circulo";
  //Object *obj = new Object(name,  3);
  Object *obj = new Object(name);

  //Setting shapes and meshes to object

  //obj->setShape(circle);
  //obj->setShape(floorPlane);
  //obj->setShape(backPlane);
  obj->setMesh(mesh);
  //obj->setShape(cylinder);
  //obj->setShape(cone);  


  //Setting lights

  Intensity ambientIntensity = Intensity(0.3, 0.3, 0.3);
  AmbientLight *ambientLight = new AmbientLight(ambientIntensity);
  Intensity pointIntensity = Intensity(0.7, 0.7, 0.7);
  PointLight *pointLight =new PointLight(pointIntensity, Coordinate(0,0,50));//Coordinate(0,60,-30))

  //Creating the scene
  Scene *scene = new Scene();

  scene->setObject(obj);



  scene->setLight(ambientLight);
  // scene->setLightAt(1, dirLight);
  scene->setLight(pointLight);

  scene->setBackgroundCoefs(bgIntensity);

  // Canvas creation
  Matrix<Color,nLines,nColumns> * m = new Matrix<Color,nLines,nColumns>();
  Canvas<nLines,nColumns> *canvas = new Canvas<nLines,nColumns>(m);

  //Canvas Loop
  for (int l = 0; l < nLines; l++) {
    double y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      double x = -wj / 2 + dx / 2 + c * dx;
      Vector3D dr = Vector3D(Coordinate(x, y, canvasDistance) - Po);
      dr.normalize();
      Intensity reflectCoefs = Space3D::TraceRay(scene, Po, dr, 1, INF);
      canvas->setColorAt(l, c, (whiteColor * reflectCoefs));
    }
  }
  //Write to file(will be changed)
  writePPM<nLines,nColumns>(canvas);

  return 0;
}