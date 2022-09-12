#include "Canvas.h"
#include "Color.h"
#include "Coordinate.h"
#include "DataConsts.h"
#include "Light.h"
#include "Matrix.h"
#include "Object.h"
#include "Scene.h"
#include "Shapes.h"
#include "Space3D.h"
#include "Vector.h"
#include <fstream>
#include <iostream>

bool writePPM(Canvas *canvas);
int main() {

  Coordinate O = Coordinate(0, 0, 0);
  Coordinate Po = O;
  int wj = 500;
  int hj = 500;

  int nLines = 500;
  int nColumns = 500;
  float dx = wj / nColumns;
  float dy = hj / nLines;
  int distance = 100;
  int sphere_distance = 100;
  // inicialização da cena e da esfera
  int radius = 500;

  Coordinate center = Coordinate(0, 0, -(sphere_distance + radius));
  Color sphereColor = {255, 0, 0};
  Circle *circle = new Circle(center, radius, sphereColor);

  Scene *scene = new Scene(1, 2);
  char name[] = "circulo";
  Object *obj = new Object(name, 1);

  obj->setShape(circle);

  AmbientLight *ambientLight = new AmbientLight(0.3);
  DirectionalLight *dirLight =
      new DirectionalLight(0.7, Vector(0, 0, -(sphere_distance + radius)));

  scene->setObjectAt(0, obj);

  Color bgColor = Color{100, 100, 100};

  scene->setLightAt(0, ambientLight);
  scene->setLightAt(1, dirLight);

  scene->setBackgroundColor(bgColor);
  // inicialização do canvas

  Canvas *canvas = new Canvas(new Matrix<Color>(nLines, nColumns), nLines,
                              nColumns); // fazer

  for (int l = 0; l < nLines; l++) {
    float y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      float x = -wj / 2 + dx / 2 + c * dx;
      Vector dr = Vector(Coordinate(x, y, -distance) - Po);

      Color color = Space3D::TraceRay(scene, O, dr, 1, INF);
      canvas->setColorAt(l, c, color);
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