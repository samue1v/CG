#include <stdio.h>
#include "MeshUtils.h"


Vertex::Vertex(){}

Vertex::Vertex(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}
Vertex::Vertex(Coordinate c){
    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
}

std::ostream& operator<<(std::ostream& os,Vertex& v){
    os <<"Vertex:\n";
    os << v.x;
    os<< " ";
    os << v.y;
    os<< " ";
    os << v.z;
    os<<"\n";
    return os;
}

Face::Face(){}

Face::Face(int v1, int v2, int v3,int n,int v1t,int v2t,int v3t){
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->v1t = v1t;
    this->v2t = v2t;
    this->v3t = v3t;
    this->n = n;

}

std::ostream& operator<<(std::ostream& os,Face& f){
    os <<"Face:\n";
    os << "v1:"<<f.v1;
    os<< " ";
    os << "v2:"<<f.v2;
    os<<" ";
    os << "v3:"<<f.v3;
    os<<" ";
    os << "n:"<<f.n;
    os<<"\n";
    os << "vt1:"<<f.v1t;
    os<<" ";
    os << "vt2:"<<f.v2t;
    os<<" ";
    os << "vt3:"<<f.v3t;
    os<<"\n";
    return os;
}

UVTex::UVTex(){}

UVTex::UVTex(double u, double v) : u(u), v(v){}

std::ostream& operator<<(std::ostream& os,UVTex& uvtex){
    os << "UVCoords:\n";
    os << "u:"<< uvtex.u;
    os << " v:"<< uvtex.v;
    os << "\n";
    return os;
}