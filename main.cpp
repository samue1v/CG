//#include "Scene.cpp"
#include "canvas.cpp"
#include "ds.h"
#include "viewport.cpp"
#include <fstream>
#include <iostream>
/* coisas pra mudar:
- trocar int pra float
- ver os comentarios no codigo e ajeitar as coisas
- testar e corrigir erros se aparecer
- fazer aparecer as cores na tela
*/
bool writePPM(Canvas *canvas);
int main() {
  std::cout<<"aqui";
  Coordinate O = Coordinate(0, 0, 0);
  Coordinate Po = O;
  int hj = 500;
  int wj = 500;
  int nLines = 500;
  int nColumns = 500;
  float dx = wj / nColumns;
  float dy = hj / nLines;
  int distance = 100;
  // inicialização da cena e da esfera
  int radius = 50;
  Coordinate center = Coordinate(0, 0, -(distance + radius));
  Color sphereColor = {255, 0, 0};
  Circle c = Circle(center, radius, sphereColor);
  Scene scene = Scene(1);
  scene.setPolygon(0, &c);
  Color bgColor = Color{100, 100, 100};
  scene.setBackgroundColor(bgColor);
  // inicialização do canvas
  Canvas canvas = Canvas(); // fazer

  for (int l = 0; l < nLines; l++) {
    float y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      float x = -wj / 2 + dx / 2 + c * dx;
      Vector dr = Vector(Coordinate(x, y, -distance) - Po);
      Color color = Viewport<float>::TraceRay(scene, O, dr, 1,
                                              INF); // lembra de perguntar
      canvas.setColorAt(x, y, color);
    }
  }
  
  writePPM(&canvas);

  return 0;
}

bool writePPM(Canvas *canvas) {
  std::ofstream myfile;
  Matrix<Color> *m = canvas->getCanvas();
  myfile.open("image.ppm");
  myfile << "P6\n";
  myfile << 500 << ' ' << 500 << "\n";
  myfile << 255 << "\n";
  for (int i = 0; i < canvas->getNumberLines(); i++) {
    for (int j = 0; j < canvas->getNumberColumns(); j++) {
      myfile << m->getVal(i, j).red << m->getVal(i, j).green
             << m->getVal(i, j).blue;
    }
  }
}