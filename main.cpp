//#include "Scene.cpp"
#include <fstream>
#include <iostream>
#include "Canvas.h"
#include "DataConsts.h"
#include "Polygons.h"
#include "Coordinate.h"
#include "Viewport.h"
#include "Scene.h"
#include "Color.h"
#include "Vector.h"
#include "Matrix.h"
/* coisas pra mudar:
- trocar int pra float
- ver os comentarios no codigo e ajeitar as coisas
- testar e corrigir erros se aparecer
- fazer aparecer as cores na tela
*/
bool writePPM(Canvas *canvas);
int main()
{

  Coordinate O = Coordinate(0, 0, 0);
  Coordinate Po = O;
  int wj = 500;
  int hj = 500;

  int nLines = 500;
  int nColumns = 500;
  float dx = wj / nColumns;
  float dy = hj / nLines;
  int distance = 5;
  // inicialização da cena e da esfera
  int radius = 100;

  Coordinate center = Coordinate(0, 0, -(distance + radius));
  Color sphereColor = {255, 0, 0};
  Circle *circle = new Circle(center, radius, sphereColor);

  Scene *scene = new Scene(1);

  scene->setPolygon(0, circle);

  Color bgColor = Color{100, 100, 100};

  scene->setBackgroundColor(bgColor);
  // inicialização do canvas
  // Por algum motivo circle não está em scene como deveria
  // lembrar que o vector deve ser um vector de ponteiros para
  // Polygons, ou seja ,elements deve ser Polygon ** element

  Canvas *canvas = new Canvas(new Matrix<Color>(nLines, nColumns), nLines, nColumns); // fazer
  // exit(-1);
  // trocar para vector
  for (int l = 0; l < nLines; l++)
  {
    float y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++)
    {
      float x = -wj / 2 + dx / 2 + c * dx;
      Vector dr = Vector(Coordinate(x, y, -distance) - Po);

      Color color = Viewport<float>::TraceRay((scene), O, dr, 1, INF);

      // lembra de perguntar
      canvas->setColorAt(l, c, color);
    }
  }

  writePPM(canvas);

  return 0;
}

bool writePPM(Canvas *canvas)
{
  std::ofstream myfile;
  Matrix<Color> *m = canvas->getCanvas();
  myfile.open("image.ppm");
  myfile << "P3\n";
  myfile << "#Gay balls\n";
  myfile << 500 << ' ' << 500 << '\n';
  myfile << 255 << '\n';
  unsigned char RGBarray[6];
  RGBarray[1] = ' ';
  RGBarray[3] = ' ';
  RGBarray[5] = ' ';

  for (int i = 0; i < canvas->getNumberLines(); i++)
  {
    for (int j = 0; j < canvas->getNumberColumns(); j++)
    {
      myfile << ' ' <<(int)m->getVal(i, j).red << ' ' <<(int)m->getVal(i, j).green << ' '
             <<(int)m->getVal(i, j).blue << ' ';
    }
    myfile << '\n';
  }
  return true;
}