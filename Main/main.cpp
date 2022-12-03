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
#include <SDL2/SDL_image.h>


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
  SDL_Renderer * renderer = nullptr;
  Coordinate O = Coordinate(0, 0, 0);
  /*
  Coordinate eye = Coordinate(0,50,30);
  Coordinate up = Coordinate(0,101,30);
  Coordinate lookAt = Coordinate(0,0,-260);
  */
  /*
   Coordinate eye = Coordinate(0,200,-100);
  Coordinate up = Coordinate(0,500,-100);
  Coordinate lookAt = Coordinate(0,0,-100);
  */
  
   Coordinate eye = Coordinate(0,0,-50);
  Coordinate up = Coordinate(0,500,-50);
  Coordinate lookAt = Coordinate(0,0,-200);
  
  
  /*
  Coordinate eye = Coordinate(0,0,10);
  Coordinate up = Coordinate(0,500,10);
  Coordinate lookAt = Coordinate(0,0,-100);
  */
  Camera * camera = new Camera(eye,lookAt,up);
  //Coordinate c = camera.getEye();
  //std::cout<<"jao: "<<c;

  Matrix<double,4,1> eyematrix = Matrix<double,4,1>(eye);
  //std::cout<<eyematrix;
  Matrix<double,4,4> cameraMatrix = camera->getWorldToCamera();
  //std::cout<<"cameraMatrix: "<<cameraMatrix<<"\n";
  Matrix<double,4,1> tmatrix = camera->getWorldToCamera()*eyematrix;
  //std::cout<< eyematrix;
  //std::cout<<"\n" <<cameraMatrix;
  //std::cout<<"\n"<<tmatrix;
  Coordinate P0 = (tmatrix).toCoordinate();
  //std::cout<<"P0:"<<P0;
  


  Intensity bgIntensity = Intensity(0, 0, 0);
  Color whiteColor = Color(255, 255, 255);
  double wj = 60;
  double hj = 60;

  const int nLines = 500;
  const int nColumns = 500;
  double dx = wj / nColumns;
  double dy = hj / nLines;
  double canvasDistance = -30;
  double sphereDistance = 60;
  // double sphere_distance = 100;
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
  Cylinder * cylinder = new Cylinder(Coordinate(0,0,-100),Vector3D(0,1,0),radius/3,3*radius,cooper);
  Coordinate cylinderTop = (cylinderAxis*3*radius)+center;
  
  //Cone
  double coneRadius = 1.5*radius;
  //Cone * cone = new Cone(cylinderTop,cylinderAxis,coneRadius,coneRadius/3,marble);
  Cone * cone = new Cone(center+Coordinate(0,50,300),cylinderAxis,coneRadius,coneRadius,marble);
  //Cone * cone = new Cone(Coordinate(0,0,-100),Vector3D(-1,0,0),radius,radius*2,marble);

  //Planes
	Coordinate floorPoint = Coordinate(0,-100,0);
	Vector3D floorNormal = Vector3D(0,sqrt(2),1);
  Coordinate backPoint = Coordinate(0,0,-400);
	Vector3D backNormal = Vector3D(0,0,-1);
	Plane *floorPlane = new Plane(floorPoint, floorNormal, rubber);
	Plane *backPlane = new Plane(backPoint, backNormal, metal);
  floorPlane->setTexture("../TextureFiles/wood.png",renderer);
  circle->setTexture("../TextureFiles/basketball1.png",renderer);
  backPlane->setTexture("../TextureFiles/floor.png",renderer);

  //Meshes
  std::string path = "../MeshFiles/cube.obj";
  Mesh * mesh = new Mesh(path,marble);
  mesh->setTransform(new Translate(0,0,-300));
  mesh->setTransform(new Scale(2,0.3,1));
  mesh->setTransform(new RotateY(90));
  //mesh->setTransform(new RotateX(-45));
  //mesh->setTransform(new RotateZ(30));
  //mesh->setTransform(new ShearYX(30));
  


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

  Intensity ambientIntensity = Intensity(0.5, 0.5, 0.5);
  AmbientLight *ambientLight = new AmbientLight(ambientIntensity);
  Intensity pointIntensity = Intensity(0.7, 0.7, 0.7);
  PointLight *pointLight =new PointLight(pointIntensity, Coordinate(0,0,00));//Coordinate(0,60,-30))
  PointLight *pointLight2 =new PointLight(pointIntensity, Coordinate(0,0,-499));
  DirectionalLight * dirLight = new DirectionalLight(Intensity(0.2,0.2,0.2),Vector3D(0,0,-1));
  //Creating the scene
  Scene *scene = new Scene();
  
  scene->setObject(obj);



  //scene->setLight(ambientLight);
  //scene->setLight(dirLight);
  scene->setLight(pointLight);
  //scene->setLight(pointLight2);

  scene->setBackgroundCoefs(bgIntensity);
  
  scene->setCamera(camera);
  Coordinate t = scene->getCamera()->getEye();
  std::cout<<t;

  scene->transformView();

  // Canvas creation
  Matrix<Color,nLines,nColumns> * m = new Matrix<Color,nLines,nColumns>();
  Canvas<nLines,nColumns> *canvas = new Canvas<nLines,nColumns>(m);
  
  //Canvas Loop
  for (int l = 0; l < nLines; l++) {
    double y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      double x = -wj / 2 + dx / 2 + c * dx;
      Coordinate canvasPoint = Coordinate(x, y, canvasDistance);
      Vector3D dr = Vector3D(canvasPoint - P0);
      dr.normalize();
      Pair<Intensity,Color> hitData = Space3D::TraceRay(scene, P0, dr, 1, INF);
      if(hitData.right.hasInit){
        //std::cout<<"aqui\n";
        canvas->setColorAt(l, c, ((hitData.right) * hitData.left));
      }
      else{
        canvas->setColorAt(l, c, (whiteColor * hitData.left));
      }
    }
  }
  //Matrix<double,4,4> msd = scene->getCamera().getTransformMatrix();
  //std::cout<< msd;
  //Matrix<double,4,4> teste = camera->getTransformMatrix();
  //std::cout<< teste;
  //Write to file(will be changed)
  writePPM<nLines,nColumns>(canvas);

  return 0;
}