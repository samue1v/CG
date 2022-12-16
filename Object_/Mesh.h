#ifndef MESH_H
#define MESH_H
#include "../DataStructures/MeshUtils.h"
#include "../DataStructures/Triple.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Matrix.h"
#include "Texture.h"
#include "Material.h"
#include <string>
#include "Transformation.h"
#include "Shapes.h"
#include <fstream>

class Mesh{
    private:
    std::string name;
    Texture * texture;
    Face intersectedFace;
    Array<Vertex> vertexList;
    Array<Vector3D> normalList;
    Array<Face> faceList;
    Array<UVTex> uvList;
    Array<Transformation *> transformList;
    Material * material;
    Vector3D intersectedNormal;
    void tempTransform(Vertex t);
    Matrix<double,4,4> stackedTranslateMatrix;
    Matrix<double,4,4> transformMatrix;
    Matrix<double,4,4> inverseMatrix;
    void applyTransform();
    void applyTransform(Coordinate point);
    Triple<int,int,int> parseFaceData(const std::string & line);
    void parseV(const std::string & line);
    void parseN(const std::string & line);
    void parseF(const std::string & line);
    void parseT(const std::string & line);
    void parseFile(std::ifstream & file);
    Mesh * cluster;
    
    public:
    Mesh();
    Mesh(const std::string & filePath);
    Mesh(const std::string & filePath,Material * material);
    Mesh(const std::string & filePath,Material * material,std::string name);
    Vector3D computeNormal();
    Material * getMaterial();
    bool setTexture(const std::string & filePath,SDL_Renderer * renderer);
    Texture * getTexture();
    Color getTexel(Coordinate P,Coordinate O,Matrix<double,4,4> cameraToWorld);
    bool setTransform(Transformation * t);
    double IntersectRay(Coordinate O,Vector3D D,double t_min,double t_max);
    void transformView(Matrix<double,4,4> transformMatrix);
    std::string getName();
    void setCluster(Mesh * cluster);
    Mesh * getCluster();
};





#endif