#ifndef MESH_U
#define MESH_U
#include "Coordinate.h"
#include "Triple.h"
#include "Pair.h"
#include "Array.h"
struct Vertex{
    Vertex(){};
    Vertex(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vertex(Coordinate c){
        this->x = c.x;
        this->y = c.y;
        this->z = c.z;
    }

    double x;
    double y;
    double z;
};
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

struct Edge{
    Edge(){}
    Edge(int v1, int v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    int v1;
    int v2;
};
std::ostream& operator<<(std::ostream& os,Edge& e){
    os <<"Edge:\n";
    os << e.v1;
    os<< " ";
    os << e.v2;
    os<<"\n";
    return os;
}

struct Face{
    Face(){}
    Face(int v1, int v2, int v3,int n){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        this->n = n;
        edges.push(Edge(v1,v3));
        edges.push(Edge(v3,v2));
        edges.push(Edge(v2,v1));

    }
    Array<Edge> edges;
    int v1;
    int v2;
    int v3;
    int n;
};
std::ostream& operator<<(std::ostream& os,Face& f){
    os <<"Face:\n";
    os << f.v1;
    os<< " ";
    os << f.v2;
    os<<" ";
    os << f.v3;
    os<<" ";
    os << f.n;
    os<<"\n";
    return os;
}
#endif
