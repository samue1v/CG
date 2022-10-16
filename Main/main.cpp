/*
- criar uma classe para coeficiente/reflectividade/intensidade, substituindo
Color ok
- criar uma classe Material
- separar o calculo da intensidade difusa e da especular (precisa de uma
reflectividade diferente para cada uma das duas)
- reflectividade para luz ambiente (Ka)
- verificar a implementação dos operadores @ ok
- manter os valores referente a cor entre 0 e 1, apenas multiplicar por 255 ok

-- checar na linha 59 e 62 se Intensity precisa ser ponteiro ou não ok

-- checar herança de reflect
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
#include "../World/Scene.h"
#include "../World/Space3D.h"
#include <math.h>
#include <fstream>
#include <iostream>

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

int main() {

  Coordinate O = Coordinate(0, 0, 0);
  Coordinate Po = Coordinate(0,0,0);
  Color whiteColor = Color(255, 255, 255);
  double wj = 60;
  double hj = 60;

  const int nLines = 500;
  const int nColumns = 500;
  double dx = wj / nColumns;
  double dy = hj / nLines;
  double canvasDistance = 30;
  double sphereDistance = 60;
  // double sphere_distance = 100;
  // inicialização da cena e da esfera
  double radius = 40;

  Coordinate center = Coordinate(0, 0, -(sphereDistance + radius));
  Rubber *rubber = new Rubber();
  Metal *metal = new Metal();
  Plastic *plastic = new Plastic();
  Cooper *cooper = new Cooper();

  Sphere *circle = new Sphere(center, radius, rubber);
  Cylinder * cylinder = new Cylinder(center,Vector(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3)),radius/3,3*radius,cooper);

	Coordinate floorPoint = Coordinate(0,-radius,0);
	Vector floorNormal = Vector(0,1,0);

	Coordinate backPoint = Coordinate(0,0,-200);
	Vector backNormal = Vector(0,0,1);
	//planeNormal.normalize();
	Plane *floorPlane = new Plane(floorPoint, floorNormal, metal);
	Plane *backPlane = new Plane(backPoint, backNormal, plastic);
  Scene *scene = new Scene(1, 2);
  char name[] = "circulo";
  Object *obj = new Object(name,  4);

  obj->setShape(circle);
  obj->setShape(floorPlane);
  obj->setShape(backPlane);
  obj->setShape(cylinder);
  Intensity ambientIntensity = Intensity(0.3, 0.3, 0.3);
  AmbientLight *ambientLight = new AmbientLight(ambientIntensity);
  Intensity pointIntensity = Intensity(0.7, 0.7, 0.7);
  PointLight *pointLight =new PointLight(pointIntensity, Coordinate(0,60,-30));//Coordinate(0,60,-30))



  scene->setObjectAt(0, obj);

  Intensity bgIntensity = Intensity(0, 0, 0);

  scene->setLightAt(0, ambientLight);
  // scene->setLightAt(1, dirLight);
  scene->setLightAt(1, pointLight);

  scene->setBackgroundCoefs(bgIntensity);
  // inicialização do canvas

  Matrix<Color,nLines,nColumns> * m = new Matrix<Color,nLines,nColumns>();


  Canvas<nLines,nColumns> *canvas = new Canvas<nLines,nColumns>(m); // fazer

  for (int l = 0; l < nLines; l++) {
    double y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      double x = -wj / 2 + dx / 2 + c * dx;
      // std::cout <<"dx: " <<dx<<" dy: " << dy <<"\n";
      Vector dr = Vector(Coordinate(x, y, -canvasDistance) - Po);
      dr.normalize();
      Intensity reflectCoefs = Space3D::TraceRay(scene, Po, dr, 1, INF);
      // reflectCoefs.normalize();//erro aqui, normalizando tudo
      canvas->setColorAt(l, c, (whiteColor * reflectCoefs));
    }
  }
  //std::cout << "passei\n";
  writePPM<nLines,nColumns>(canvas);

  return 0;
}



