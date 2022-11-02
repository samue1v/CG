#ifndef OBJECTS_HEADER
#define OBJECTS_HEADER
#include <stdio.h>
#include "../DataStructures/Array.h"
#include "Mesh.h"
#include "Shapes.h"
class Object{
    public:
        Object();
        Object(char *name);
        int getShapeCount();
        int getMeshCount();
        char * getName();
        bool setName(char * newName);
        bool setShape(Shape3D * shape);
        bool setMesh(Mesh * newMesh);
        Mesh * getMeshAt(int index);
        Shape3D * getShapeAt(int index);


    private:
        Array<Mesh*> meshes;
        Array<Shape3D*> shapes;
        char *name;

};
#endif
