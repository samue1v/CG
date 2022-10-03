#ifndef OBJECTS_HEADER
#define OBJECTS_HEADER
#include <stdio.h>
#include "Shapes.h"
class Object{
    public:
        Object();
        Object(char *name,int numberOfShapes);
        int getShapeCount();
        char * getName();
        bool setName(char * newName);
        bool setShape(Shape3D * shape);
        bool setShapeAt(Shape3D * shape,int index);
        Shape3D * getShapeAt(int index);


    private:
        int shapeNumMax;
        int shapeCount;
        Shape3D ** shapes;
        char *name;

};
#endif