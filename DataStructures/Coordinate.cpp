#include "Coordinate.h"
#include <iostream>

Coordinate::Coordinate() {}

Coordinate::Coordinate(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

std::ostream& operator<<(std::ostream& os,Coordinate& c){
    os <<"Coordinate:\n";
    os << c.x;
    os<< " ";
    os << c.y;
    os<<" ";
    os << c.z;
    os<<"\n";
    return os;
}