#include <stdio.h>
#include "ds.h"
class Camera{
    public:
        bool setPos(coordinate cords);
        coordinate getPos();
    private:
        coordinate pos;
};

bool Camera::setPos(coordinate cords){
    this->pos = cords;     
    return true;
}

coordinate Camera::getPos(){
    return this->pos;
}