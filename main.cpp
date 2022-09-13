/*
- criar uma classe para coeficiente/reflectividade/intensidade, substituindo Color
- criar uma classe Material
- verificar a implementação dos operadores @
- manter os valores referente a cor entre 0 e 1, apenas multiplicar por 255 
*/
#include "Canvas.h"
#include "Color.h"
#include "Reflect.h"
#include "Coordinate.h"
#include "DataConsts.h"
#include "Light.h"
#include "Matrix.h"
#include "Object.h"
#include "Scene.h"
#include "Shapes.h"
#include "Space3D.h"
#include "Vector.h"
#include "Reflect.h"
#include <fstream>
#include <iostream>

bool writePPM(Canvas *canvas);
int main() {

  Coordinate O = Coordinate(0, 0, 0);
  Coordinate Po = O;
  int whiteColor = 255;
  int wj = 60;
  int hj = 60;

  int nLines = 500;
  int nColumns = 500;
  float dx = wj / nColumns;
  float dy = hj / nLines;
  int distance = 30;
  int sphere_distance = 100;
  // inicialização da cena e da esfera
  int radius = 40;

  Coordinate center = Coordinate(0, 0, -(distance+radius)*2);
  
  Reflectiveness sphereK = {0.7, 0.2, 0.2};
  
  Circle *circle = new Circle(center, radius, sphereK);

  Scene *scene = new Scene(1, 1);
  char name[] = "circulo";
  Object *obj = new Object(name, 1);

  obj->setShape(circle);

  AmbientLight *ambientLight = new AmbientLight(0.3);
  // *dirLight = new DirectionalLight(0.2, Vector(0, 0, -1));
  PointLight *pointLight = new PointLight(0.7,Coordinate(0,60,-30));
  scene->setObjectAt(0, obj);

  Color bgColor = Color{100, 100, 100};

  scene->setLightAt(0, ambientLight);
  //scene->setLightAt(1, dirLight);
  scene->setLightAt(1, pointLight);

  scene->setBackgroundColor(bgColor);
  // inicialização do canvas

  Canvas *canvas = new Canvas(new Matrix<Color>(nLines, nColumns), nLines,
                              nColumns); // fazer

  for (int l = 0; l < nLines; l++) {
    float y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      float x = -wj / 2 + dx / 2 + c * dx;
      Vector dr = Vector(Coordinate(x, y, -distance) - Po);
      dr.normalize();
      Reflectiveness reflectCoefs = Space3D::TraceRay(scene, Po, dr, 1, INF);
      canvas->setColorAt(l, c, Color(reflectCoefs*whiteColor));
    }
  }

  writePPM(canvas);

  return 0;
}

bool writePPM(Canvas *canvas) {
  std::ofstream myfile;
  Matrix<Color> *m = canvas->getCanvas();
  myfile.open("image.ppm");
  myfile << "P3\n";
  myfile << 500 << ' ' << 500 << '\n';
  myfile << 255 << '\n';
  unsigned char RGBarray[6];
  RGBarray[1] = ' ';
  RGBarray[3] = ' ';
  RGBarray[5] = ' ';

  for (int i = 0; i < canvas->getNumberLines(); i++) {
    for (int j = 0; j < canvas->getNumberColumns(); j++) {
      myfile << ' ' << (int)m->getVal(i, j).red << ' '
             << (int)m->getVal(i, j).green << ' ' << (int)m->getVal(i, j).blue
             << ' ';
    }
    myfile << '\n';
  }
  return true;
}