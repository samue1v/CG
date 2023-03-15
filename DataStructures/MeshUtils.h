#ifndef MESH_U
#define MESH_U
#include "Coordinate.h"
#include "Triple.h"
#include "Pair.h"
#include "Array.h"
struct Vertex{
    Vertex();
    Vertex(float x, float y, float z);
    Vertex(Coordinate c);
    friend std::ostream& operator<<(std::ostream& os, Vertex& a);
    float x;
    float y;
    float z;
    Vertex operator+(Vertex right) {
        return Vertex(x + right.x, y + right.y, z + right.z);
    }
    Vertex operator*(Vertex right) {
        return Vertex(x * right.x, y * right.y, z * right.z);
    }
    Vertex operator*(float right) {
        return Vertex(x * right, y * right, z * right);
    }
};


struct Face{
    Face();
    Face(int v1, int v2, int v3,int n,int v1t,int v2t,int v3t);
    friend std::ostream& operator<<(std::ostream& os, Face& a);
    int v1;
    int v2;
    int v3;
    int n;
    int v1t;
    int v2t;
    int v3t;
    float faceArea;
    float v1W;
    float v2W;
    float v3W;
};

struct UVTex{
    UVTex();
    UVTex(float u,float v);
    friend std::ostream& operator<<(std::ostream& os, UVTex& uvtex);
    float u;
    float v;
};



#endif
