#include <iostream>
#include "../Camera/Camera.h"
#include "../DataStructures/Coordinate.h"

int main(){
    Camera camera = Camera(Coordinate(10,0,0),Coordinate(2,0,0),Coordinate(10,10,0));
    //std::cout << camera.transformMatrix;
    Matrix<double,4,4> * m = new Matrix<double,4,4>();
    Matrix<double,4,4> * n = m;
    m->setVal(0,0,1);
    std::cout << *n;

}