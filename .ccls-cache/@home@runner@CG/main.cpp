#include <iostream>
#include "ds.h"

int main() {
  Coordinate O = Coordinate(0,0,0);
  Coordinate Po = O;
  int hj = 500;
  int wj = 500;
  int nLines = 500;
  int nColumns = 500;
  int dx = wj/nColumns;
  int dy = hj/nLines;
  int distance = 100;
  Scene scene = Scene(); //fazer
  Canvas canvas = Canvas(); //fazer
  
  for (int l = 0; l < nLines; l++ ){
    int y = hj/2 - dy/2 - l*dy;
    for (int c = 0; c < nColumns; c++ ){
      int x = -wj/2 + dx/2 + c*dx;
      Vector dr = Vector(Coordinate(x,y,-distance) - Po);
      Color color = TraceRay(scene, O, dr, 1, INF);
      canvas.PutPixel(x, y, color);
    }
  }
  
  return 0;
}