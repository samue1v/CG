#ifndef CANVAS_H
#define CANVAS_H
#include "../DataStructures/Matrix.h"
#include "../Object_/Object.h"
#include "../Ilumination/Color.h"

template <int l,int k>
class Canvas{
    public:
      Canvas();
      bool setColorAt(int x, int y, Color c);
      bool setObjectAt(int x,int y, Object * o);
      Matrix<Object *,l,k> * getCanvas();
      int getNumberLines();
      int getNumberColumns();
      u_int8_t * getColorBuffer();
      Color getColorAt(int i,int j);
      bool pushColorBuffer(Color c);
      void clearCanvas();
    private:
      int colorBufferCount;
      u_int8_t * colorBuffer;
      int nLines;
      int nColumns;
      Matrix<Object *,l,k> * canvas;
};
template <int l, int k>
Canvas<l,k>::Canvas(){
  this->canvas = new Matrix<Object *,l,k>();
  this->nLines = l;
  this->nColumns = k;
  this->colorBuffer = new u_int8_t[l*k*3];
  this->colorBufferCount = 0;
}

template <int l, int k>
int Canvas<l,k>::getNumberLines(){
  return this->nLines;
}
template <int l, int k>
int Canvas<l,k>::getNumberColumns(){
  return this->nColumns;
}

template <int l, int k>
Matrix<Object *,l,k> * Canvas<l,k>::getCanvas(){
  return (this->canvas);
}
/*
template <int l, int k>
bool Canvas<l,k>::setColorAt(int x, int y, Color c){
  return (*this->canvas).setVal(x,y,c); 
}
*/
template <int l, int k>
Color Canvas<l,k>::getColorAt(int i,int j){
  int begin = (i*l + j)*3;
  Color c = Color(colorBuffer[begin],colorBuffer[++begin],colorBuffer[++begin]);
  //std::cout<<c;
  return c;
}

template <int l, int k>
void Canvas<l,k>::clearCanvas(){
  std::fill(colorBuffer,colorBuffer+(l*k*3),0);
  colorBufferCount = 0;
}

template <int l, int k>
bool Canvas<l,k>::setObjectAt(int x,int y,Object * o){
  return (*this->canvas).setVal(x,y,o); 
}

template <int l, int k>
uint8_t * Canvas<l,k>::getColorBuffer(){
  return this->colorBuffer;
}
template <int l, int k>
bool Canvas<l,k>::pushColorBuffer(Color c){
  //std::cout<<c;
  colorBuffer[colorBufferCount++] = c.red;
  colorBuffer[colorBufferCount++] = c.green;
  colorBuffer[colorBufferCount++] = c.blue;
  //std::cout<<colorBufferCount<<"\n";
  //exit(-1);
  return true;
}

//uma observação, talvez, depois que seja preenchido o buffer pela primeira vez, o contador
//tenha que ser resetado, caso contrário ocorrerá um seg fault
#endif