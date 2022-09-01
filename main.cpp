#include <iostream>
#include "ds.h"
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
  Scene scene = Scene(); //fazer
  Canvas canvas = Canvas(); //fazer
  
  for (int l = 0; l < nLines; l++ ){
    float y = hj/2 - dy/2 - l*dy;
    for (int c = 0; c < nColumns; c++ ){
      float x = -wj/2 + dx/2 + c*dx;
      Vector dr = Vector(Coordinate(x,y,-distance) - Po);
      Color color = TraceRay(scene, O, dr, 1, INF);
      canvas.PutPixel(x, y, color);
    }
  }
  
  return 0;
}