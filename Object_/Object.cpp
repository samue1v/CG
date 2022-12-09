#include <stdio.h>
#include "Object.h"
#include "Mesh.h"

Object::Object(){};

Object::Object(char *name) : name(name){
    //this->shapes={nullptr};
}


int Object::getShapeCount(){
    return (this->shapes).getSize();
}

int Object::getMeshCount(){
    return (this->meshes).getSize();
}
char * Object::getName(){
    return this->name;
}

bool Object::setName(char * newName){
    this->name = newName;
    return true;
}

bool Object::setShape(Shape3D * shape){
    (this->shapes).push(shape);
    return true;
}

bool Object::setMesh(Mesh * newMesh){
    (this->meshes).push(newMesh);
    return true;
}

Mesh * Object::getMeshAt(int index){
    return this->meshes.getElementAt(index);
}

Shape3D * Object::getShapeAt(int index){
    
    return (this->shapes).getElementAt(index);
}

void Object::applyViewTransform(Matrix<double,4,4> transformMatrix){
    for(int i = 0;i<this->shapes.getSize();i++){
        shapes.getElementAt(i)->transformView(transformMatrix);
    }
    for(int j = 0;j<this->meshes.getSize();j++){
        meshes.getElementAt(j)->transformView(transformMatrix);
    }
}

bool Object::setTransform(Transformation * t){
    for(int i = 0;i<shapes.getSize();i++){
        shapes.getElementAt(i)->setTransform(t);
    }
    for(int j = 0;j<meshes.getSize();j++){
        meshes.getElementAt(j)->setTransform(t);
    }
    return true;
}