#include "Mesh.h"
#include "../DataStructures/MeshUtils.h"
#include "../DataStructures/Triple.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/DataConsts.h"
#include "../DataStructures/Matrix.h"
#include "Shapes.h"
#include <string>
#include <iostream>

Mesh::Mesh(){
}

Mesh::Mesh(const std::string & filePath){
    std::ifstream file;
    file.open(filePath);
    parseFile(file);
    this->transformMatrix = Matrix<double,4,4>::identity();
    this->inverseMatrix = Matrix<double,4,4>::identity();
}

void Mesh::parseFile(std::ifstream & file){
    std::string line;
    while(file){
        getline(file,line);
        if(line[0] == 'v' && line[1]==' '){
            parseV(line.substr(line.find(" ") + 1,line.length()));
        }
        if(line[0] == 'v' && line[1]=='n'){
            parseN(line.substr(line.find(" ") + 1,line.length()));
        }
        if(line[0] == 'f'){

            parseF(line.substr(line.find(" ") + 1,line.length()));
        }

    }
    file.close();
}

Triple<int> Mesh::parseFaceData(const std::string & line){
    Array<int> a;
    Triple<int> t;
    std::string tempStr = line;
    double val;
    int index = 0;
    int len;

    while(true){
        len = tempStr.length();
        index = tempStr.find("/");

        if(index<0){
            break;
        }
        val = std::stoi(tempStr.substr(0,index));
        tempStr =tempStr.substr(index+1,len);
        a.push(val);
    }
    val = std::stoi(tempStr);
    a.push(val);
    t.left = a.getElementAt(0);
    t.middle = a.getElementAt(1);
    t.right = a.getElementAt(2);
    return t;

}
void Mesh::parseV(const std::string & line){
    Array<double> a;
    std::string delimiter = " ";
    std::string tempStr = line;
    std::string valueStr;
    int index = 0;
    double val;
    int length;
    while(!tempStr.empty() && index >= 0){
        length = (int)tempStr.length();
        index = tempStr.find(delimiter);
        valueStr = tempStr.substr(0,index);
        tempStr = tempStr.substr(std::min(index+1,length),length);
        val = std::stod(valueStr);
        a.push(val);
    }
    this->vertexList.push(Vertex(a.getElementAt(0),a.getElementAt(1),a.getElementAt(2)));
}

void Mesh::parseN(const std::string & line){
    Array<double> a;
    double x,y,z;
    std::string delimiter = " ";
    std::string tempStr = line;
    std::string valueStr;
    int index = 0;
    double val;
    int length;
    while(!tempStr.empty() && index >= 0){
        length = (int)tempStr.length();
        index = tempStr.find(delimiter);
        valueStr = tempStr.substr(0,index);
        tempStr = tempStr.substr(std::min(index+1,length),length);
        val = std::stod(valueStr);
        a.push(val);
    }
    this->normalList.push(Vector(a.getElementAt(0),a.getElementAt(1),a.getElementAt(2)));
}

void Mesh::parseF(const std::string & line){

    std::string slashDelimiter = "/";
    std::string blankDelimiter = " ";
    std::string dataStr;
    std::string tempStr = line;
    Array<int> v;
    Array<int> t;
    Array<int> n;
    Triple<int> r;
    int len;
    int index = 0;
    while(!tempStr.empty() && index >= 0){
        len = tempStr.length();
        index = tempStr.find(blankDelimiter);
        dataStr = tempStr.substr(0,index);
        r = parseFaceData(dataStr);
        tempStr = tempStr.substr(std::min(index +1,len),len);
        v.push(r.left - 1);
        t.push(r.middle - 1);
        n.push(r.right - 1);
    }
    for(int i = 0;i<v.getSize();i+=3){
        Face f = Face(v.getElementAt(i),v.getElementAt(i+1),v.getElementAt(i+2),n.getElementAt(i));
        this->faceList.push(f); 
    }
}

double Mesh::IntersectRay(Coordinate O,Vector D,double t_min,double t_max){
    Coordinate V0, V1, V2;
    double b0,b1,b2;
    Plane plane;
    Face current_face;
    Vector N;
    double t_plane;
    double closest_t = INF;
    for(int i = 0;i<this->faceList.getSize();i++){
        current_face = this->faceList.getElementAt(i);
        N = this->normalList.getElementAt(current_face.n);
        V0 = Coordinate(this->vertexList.getElementAt(current_face.v1).x,this->vertexList.getElementAt(current_face.v1).y,this->vertexList.getElementAt(current_face.v1).z);
        V1 = Coordinate(this->vertexList.getElementAt(current_face.v2).x,this->vertexList.getElementAt(current_face.v2).y,this->vertexList.getElementAt(current_face.v2).z);
        V2 = Coordinate(this->vertexList.getElementAt(current_face.v3).x,this->vertexList.getElementAt(current_face.v3).y,this->vertexList.getElementAt(current_face.v3).z);
        plane = Plane(V0,N,NULL);
        t_plane = plane.IntersectRay(O,D,t_min,t_max);
        if(t_plane < t_min){
            continue;
        }
        Coordinate P = D*t_plane + O;
        Vector V0_P = Vector(V0-P);
        Vector V1_P = Vector(V1-P);
        Vector V2_P = Vector(V2-P);
        
        b0 = Vector::dot(Vector::cross(V0_P,V1_P),N);
        b1 = Vector::dot(Vector::cross(V2_P,V0_P),N);
        b1 = Vector::dot(Vector::cross(V1_P,V2_P),N);
        if(b0>0 && b1>0 && b2>0 && t_plane<closest_t){
            closest_t = t_plane;
        }   
    }
    return closest_t;
}

bool Mesh::setTransform(Transformation * t){
    (this->transformList).push(t); 
    this->transformMatrix = (this->transformMatrix) * t->getTransform();
    this->inverseMatrix = t->getInverse()*(this->inverseMatrix);
    return true;
    
}

void Mesh::applyTransform(){
    
}


