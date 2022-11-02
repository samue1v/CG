#ifndef MESH_H
#define MESH_H
#include "../DataStructures/MeshUtils.h"
#include "../DataStructures/Triple.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Matrix.h"
#include <string>
#include "Transformation.h"
#include "Shapes.h"
#include <fstream>

class Mesh{
    private:
    Array<Vertex> vertexList;
    Array<Vector> normalList;
    Array<Face> faceList;
    Array<Transformation *> transformList;
    Matrix<double,4,4> transformMatrix;
    Matrix<double,4,4> inverseMatrix;
    void applyTransform();
    bool setTransform(Transformation * t);
    Triple<int> parseFaceData(const std::string & line);
    void parseV(const std::string & line);
    void parseN(const std::string & line);
    void parseF(const std::string & line);
    void parseFile(std::ifstream & file);
    
    public:
    Mesh();
    Mesh(const std::string & filePath);
    Face getFaceAt(int index);
    Vertex getVertexAt(int index);
    Vector getNormalAt(int inde); 
    double IntersectRay(Coordinate O,Vector D,double t_min,double t_max);
};





#endif