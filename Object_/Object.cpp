#include <stdio.h>
#include "Object.h"

Object::Object(){};

Object::Object(char *name,int numberOfShapes) : name(name),shapeNumMax(numberOfShapes),shapes(new Shape3D * [numberOfShapes]) ,shapeCount(0){
    //this->shapes={nullptr};    
}


int Object::getShapeCount(){
    return this->shapeCount;
}

char * Object::getName(){
    return this->name;
}

bool Object::setName(char * newName){
    this->name = newName;
    return true;
}

bool Object::setShape(Shape3D * shape){
    if(shapeCount<shapeNumMax){
        this->shapes[shapeCount]=shape;
        shapeCount++;
        return true;

    }
    return false;
}

bool Object::setShapeAt(Shape3D * shape,int index){
    if(index<shapeNumMax && index>=0){
        int temp = shapeCount;
        if(!shapes[index]){
            shapeCount++;
        }
        this->shapes[temp]=shape;
        return true;
    }
    return false;
}

Shape3D * Object::getShapeAt(int index){
    if(index<shapeNumMax && index>=0){
        return this->shapes[index];
    }
    return nullptr;
}