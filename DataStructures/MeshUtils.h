#ifndef MESH_U
#define MESH_U
#include "Coordinate.h"
#include "Triple.h"
#include "Pair.h"
#include "Array.h"
struct Vertex{
    Vertex();
    Vertex(double x, double y, double z);
    Vertex(Coordinate c);
    friend std::ostream& operator<<(std::ostream& os, Vertex& a);
    double x;
    double y;
    double z;
    Vertex operator+(Vertex right) {
        return Vertex(x + right.x, y + right.y, z + right.z);
    }
    Vertex operator*(Vertex right) {
        return Vertex(x * right.x, y * right.y, z * right.z);
    }
    Vertex operator*(double right) {
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
    double faceArea;
    double v1W;
    double v2W;
    double v3W;
};

struct UVTex{
    UVTex();
    UVTex(double u,double v);
    friend std::ostream& operator<<(std::ostream& os, UVTex& uvtex);
    double u;
    double v;
};



#endif
