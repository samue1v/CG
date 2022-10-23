#ifndef MESH_H
#define MESH_H
#include "../DataStructures/MeshUtils.h"
#include <string>
#include "../DataStructures/Triple.h"
#include "../DataStructures/Vector.h"
#include <fstream>

class Mesh{
    private:
    Array<Vertex> vertexList;
    Array<Vector> normalList;
    Array<Face> faceList;
    std::ifstream file;
    Triple<int> parseData(const std::string & line);
    void parseV(const std::string & line);
    void parseN(const std::string & line);
    void parseF(const std::string & line);
    void parseFile();
    double IntersectRay();
    public:
    Mesh();
    Mesh(const std::string & filePath);
    Face getFaceAt(int index);
    Vertex getVertexAt(int index);
    //Edge getEdgeAt(int index);
    Vector getNormalAt(int inde); 
};





#endif