#include <stdio.h>
#include "../DataStructures/DataConsts.h"
#include "../DataStructures/Coordinate.h"

class Camera{
    public:
        bool setPos(Coordinate cords);
        Coordinate getPos();
    private:
        Coordinate pos;
};

bool Camera::setPos(Coordinate cords){
    this->pos = cords;     
    return true;
}

Coordinate Camera::getPos(){
    return this->pos;
}