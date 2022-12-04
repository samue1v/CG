/*
Lembrar de olhar o calculo da normal da malha, lembra da ordem g o f
lembra que eu mudei canvas distance pra ser positivo, logo no loop principal deve-se mudar
para -canvas_distance
*/

#include "../Canvas_/Canvas.h"
#include "../Camera/Camera.h"
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
#include "../Object_/Texture.h"
#include "../World/Scene.h"
#include "../World/Space3D.h"
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>
#include <SDL2/SDL_image.h>


template<int l,int k>
bool writePPM(Canvas<l,k> *canvas) {
  std::ofstream myfile;
  //Matrix<Color,l,k> *m = canvas->getCanvas();
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
      Color c = canvas->getColorAt(i,j);
      //std::cout<<(c);
      myfile << ' ' << (int)c.red << ' '
             << (int)c.green << ' ' << (int)c.blue
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

void constructScene(Scene & scene){
  SDL_Renderer * renderer = nullptr;
  double sphereDistance = 60;

  Coordinate eye = Coordinate(0,70 ,70);
  Coordinate up = Coordinate(0,2000,20);
  Coordinate lookAt = Coordinate(0,0,-100);  

  Camera * camera  = new Camera(eye,lookAt,up);

  // inicialização da cena e da esfera
  double radius = 100;

  Coordinate center = Coordinate(0, 0, -(sphereDistance + radius));

  //Materials
  Rubber *rubber = new Rubber();
  Metal *metal = new Metal();
  Plastic *plastic = new Plastic();
  Cooper *cooper = new Cooper();
  Marble *marble = new Marble();

  //Sphere
  Sphere *circle = new Sphere(Coordinate(0,0,-200), radius, cooper);
  

  //Cylinder
  Vector3D cylinderAxis = Vector3D(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
  Cylinder * cylinder = new Cylinder(Coordinate(0,200,-100),Vector3D(0,0,-1),100,200,marble);
  Coordinate cylinderTop = (cylinderAxis*3*radius)+center;
  
  //Cone
  double coneRadius = 1.5*radius;
  //Cone * cone = new Cone(cylinderTop,cylinderAxis,coneRadius,coneRadius/3,marble);
  Cone * cone = new Cone(center+Coordinate(0,50,300),cylinderAxis,coneRadius,coneRadius,marble);
  //Cone * cone = new Cone(Coordinate(0,0,-100),Vector3D(-1,0,0),radius,radius*2,marble);

  //Planes
	Coordinate floorPoint = Coordinate(0,0,0);
	Vector3D floorNormal = Vector3D(0,1,0);
  Coordinate backPoint = Coordinate(0,0,-400);
	Vector3D backNormal = Vector3D(0,0,-1);
	Plane *floorPlane = new Plane(floorPoint, floorNormal, rubber);
	Plane *backPlane = new Plane(backPoint, backNormal, metal);
  floorPlane->setTexture("../TextureFiles/wood.png",renderer);
  circle->setTexture("../TextureFiles/basketball1.png",renderer);
  backPlane->setTexture("../TextureFiles/floor.png",renderer);

  //Meshes
  std::string simple_mesh = "../MeshFiles/cube.obj";
   std::string casa_mesh = "../MeshFiles/casa.obj";
  Mesh * mesh = new Mesh(casa_mesh,marble);
  mesh->setTransform(new Translate(0,35,0));
  mesh->setTransform(new Scale(3,3,3));
  mesh->setTransform(new RotateY(-10));
  //mesh->setTransform(new RotateX(-90));
  //mesh->setTransform(new RotateZ(30));
  //mesh->setTransform(new ShearYX(30));
  


  //Object
  char name[] = "circulo";
  //Object *obj = new Object(name,  3);
  Object *obj = new Object(name);

  //Setting shapes and meshes to object

  //obj->setShape(circle);
  obj->setShape(floorPlane);
  //obj->setShape(backPlane);
  obj->setMesh(mesh);
  //obj->setShape(cylinder);
  //obj->setShape(cone);  

  //Setting lights

  Intensity ambientIntensity = Intensity(0.2, 0.2, 0.2);
  AmbientLight *ambientLight = new AmbientLight(ambientIntensity);
  Intensity pointIntensity = Intensity(0.7, 0.7, 0.7);
  PointLight *pointLight =new PointLight(pointIntensity, Coordinate(0,70,10));//Coordinate(0,60,-30))
  PointLight *pointLight2 =new PointLight(pointIntensity, Coordinate(0,0,-499));
  DirectionalLight * dirLight = new DirectionalLight(Intensity(0.2,0.2,0.2),Vector3D(0,0,-1));
  //Creating the scene
  
  scene.setObject(obj);



  scene.setLight(ambientLight);
  //scene->setLight(dirLight);
  scene.setLight(pointLight);
  //scene->setLight(pointLight2);
  
  scene.setCamera(camera);

  scene.transformView();
}

int main() {
  double wj = 60;
  double hj = 60;

  double canvasDistance = -30;

  const int nLines = 500;
  const int nColumns = 500;
  double dx = wj / nColumns;
  double dy = hj / nLines;

  Scene * scene = new Scene;
  
  constructScene(*scene);

  // Canvas creation
  Canvas<nLines,nColumns> *canvas = new Canvas<nLines,nColumns>();
  
  //Canvas Loop
  Coordinate P0 = scene->getCamera()->getEyeTransformed();
  for (int l = 0; l < nLines; l++) {
    double y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      double x = -wj / 2 + dx / 2 + c * dx;
      Coordinate canvasPoint = Coordinate(x, y, canvasDistance);
      Vector3D dr = Vector3D(canvasPoint - P0);
      dr.normalize();
      Triple<Object *,Intensity,Color> hitData = Space3D::TraceRay(scene, P0, dr, 1, INF);
      canvas->setObjectAt(l,c,hitData.left);
      if(hitData.right.hasInit){
        //canvas->setColorAt(l, c, ((hitData.right) * hitData.left));
        canvas->pushColorBuffer(hitData.right * hitData.middle);
      }
      else{
        //canvas->setColorAt(l, c, (scene->getNaturalColor() * hitData.left));
        canvas->pushColorBuffer(scene->getNaturalColor() * hitData.middle);
      }
    }
  }
  //Write to file(will be changed)
  writePPM<nLines,nColumns>(canvas);

  return 0;
}