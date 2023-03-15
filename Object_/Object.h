#ifndef OBJECTS_HEADER
#define OBJECTS_HEADER
#include <stdio.h>
#include "../DataStructures/Array.h"
#include "../DataStructures/Matrix.h"
#include "Transformation.h"
#include "Mesh.h"
#include "Shapes.h"
#include <string>
class Object{
    public:
        Object();
        Object(std::string name);
        int getShapeCount();
        int getMeshCount();
        std::string getName();
        bool setName(std::string newName);
        bool setShape(Shape3D * shape);
        bool setMesh(Mesh * newMesh);
        bool setTransform(Transformation * t);
        Mesh * getMeshAt(int index);
        Shape3D * getShapeAt(int index);
        void applyViewTransform(Matrix<float,4,4> transformMatrix);


    private:
        Array<Mesh*> meshes;
        Array<Shape3D*> shapes;
        std::string  name;

};
#endif
