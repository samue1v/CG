#include <iostream>
#include "../Camera/Camera.h"
#include "../DataStructures/Coordinate.h"

int main(){
    Camera camera = Camera(Coordinate(10,0,0),Coordinate(2,0,0),Coordinate(10,10,0));
    std::cout << camera.transformMatrix;

}