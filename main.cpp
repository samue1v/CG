#include <iostream>
#include <iostream>
#include <fstream>
#include "ds.h"
#include "Scene.cpp"
#include "canvas.cpp"
#include "viewport.cpp"
/* coisas pra mudar:
- trocar int pra float
- ver os comentarios no codigo e ajeitar as coisas
- testar e corrigir erros se aparecer
- fazer aparecer as cores na tela
*/
int main() {
  Coordinate O = Coordinate(0,0,0);
  Coordinate Po = O;
  int hj = 500;
  int wj = 500;
  int nLines = 500;
  int nColumns = 500;
  float dx = wj/nColumns;
  float dy = hj/nLines;
  int distance = 100;
  //inicialização da cena e da esfera
  int radius = 50;
  Coordinate center = Coordinate(0,0,-(distance + radius));
  Color sphereColor = {'255','0','0'};
  Circle c = Circle(center, radius, sphereColor);
  Scene scene = Scene(1); 
  scene.setPolygon(0,&c);
  Color bgColor = Color{'100','100','100'};
  scene.setBackgroundColor(bgColor);
  //inicialização do canvas
  Canvas canvas = Canvas(); //fazer
  
  for (int l = 0; l < nLines; l++ ){
    float y = hj/2 - dy/2 - l*dy;
    for (int c = 0; c < nColumns; c++ ){
      float x = -wj/2 + dx/2 + c*dx;
      Vector dr = Vector(Coordinate(x,y,-distance) - Po);
      Color color = Viewport<float>::TraceRay(scene, O, dr, 1, INF);//lembra de perguntar
      canvas.setColorAt(x,y,color);
    }
  }
  
  return 0;
}

bool writePPM(Canvas * canvas){
  std::ofstream myfile;
  myfile.open ("image.ppm");
  myfile << "P6\n";
  myfile << 500 <<' '<<500<<"\n";
  myfile << 255 << "\n";

}