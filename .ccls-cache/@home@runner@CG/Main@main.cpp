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
#include <fstream>
#include <iostream>

bool writePPM(Canvas *canvas);
int main() {

  Coordinate O = Coordinate(0, 0, 0);
  Coordinate Po = Coordinate(0, 0, 0);
  Color whiteColor = Color(255, 255, 255);
  float wj = 60;
  float hj = 60;

  int nLines = 500;
  int nColumns = 500;
  float dx = wj / nColumns;
  float dy = hj / nLines;
  float distance = 30;
  // float sphere_distance = 100;
  // inicialização da cena e da esfera
  float radius = 40;

  Coordinate center = Coordinate(0, 0, -(distance + radius));

  // Reflectiveness sphereK = {0.7, 0.2, 0.2};
  Rubber *material = new Rubber();
  Sphere *circle = new Sphere(center, radius, material);

  Scene *scene = new Scene(1, 2);
  char name[] = "circulo";
  Object *obj = new Object(name, 1);

  obj->setShape(circle);
  Intensity ambientIntensity = Intensity(0, 0, 0);
  AmbientLight *ambientLight = new AmbientLight(ambientIntensity);
  Intensity pointIntensity = Intensity(0.7, 0.7, 0.7);
  PointLight *pointLight =
      new PointLight(pointIntensity, Coordinate(-40, 60, 0));
  scene->setObjectAt(0, obj);

  Intensity bgIntensity = Intensity(0, 0, 0);

  scene->setLightAt(0, ambientLight);
  // scene->setLightAt(1, dirLight);
  scene->setLightAt(1, pointLight);

  scene->setBackgroundCoefs(bgIntensity);
  // inicialização do canvas

  Canvas *canvas = new Canvas(new Matrix<Color>(nLines, nColumns), nLines,
                              nColumns); // fazer

  for (int l = 0; l < nLines; l++) {
    float y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      float x = -wj / 2 + dx / 2 + c * dx;
      // std::cout <<"dx: " <<dx<<" dy: " << dy <<"\n";
      Vector dr = Vector(Coordinate(x, y, -distance) - Po);
      dr.normalize();
      Intensity reflectCoefs = Space3D::TraceRay(scene, Po, dr, 1, INF);
      // reflectCoefs.normalize();//erro aqui, normalizando tudo
      canvas->setColorAt(l, c, (whiteColor * reflectCoefs));
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