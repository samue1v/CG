#ifndef MESH_H
#define MESH_H
#include "../DataStructures/MeshUtils.h"
#include "../DataStructures/Triple.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Matrix.h"
#include "Material.h"
#include <string>
#include "Transformation.h"
#include "Shapes.h"
#include <fstream>

class Mesh{
    private:
    Array<Vertex> vertexList;
    Array<Vector3D> normalList;
    Array<Face> faceList;
    Array<Transformation *> transformList;
    Material * material;
    Vector3D intersectedNormal;
    Matrix<double,4,4> transformMatrix;
    Matrix<double,4,4> inverseMatrix;
    void applyTransform();
    Triple<int> parseFaceData(const std::string & line);
    void parseV(const std::string & line);
    void parseN(const std::string & line);
    void parseF(const std::string & line);
    void parseFile(std::ifstream & file);
    
    public:
    Mesh();
    Mesh(const std::string & filePath);
    Mesh(const std::string & filePath,Material * material);
    Vector3D computeNormal();
    Material * getMaterial();
    bool setTransform(Transformation * t);
    double IntersectRay(Coordinate O,Vector3D D,double t_min,double t_max);
};





#endif