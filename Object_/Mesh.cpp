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
    //this->stackedTransformMatrix = this->transformMatrix; 
    this->stackedTranslateMatrix = this->transformMatrix;
    this->inverseMatrix = this->transformMatrix;
    this->name = "undefined";
}

Mesh::Mesh(const std::string & filePath,Material * material){
    std::ifstream file;
    file.open(filePath);
    parseFile(file);
    this->texture = nullptr;
    this->transformMatrix = Matrix<double,4,4>::identity();
    //this->stackedTransformMatrix = this->transformMatrix; 
    this->stackedTranslateMatrix = this->transformMatrix;
    this->inverseMatrix = this->transformMatrix;
    this->material = material;
    this->name = "undefined";
}

Mesh::Mesh(const std::string & filePath,Material * material,std::string name){
    std::ifstream file;
    file.open(filePath);
    parseFile(file);
    this->texture = nullptr;
    this->transformMatrix = Matrix<double,4,4>::identity();
    //this->stackedTransformMatrix = this->transformMatrix; 
    this->stackedTranslateMatrix = this->transformMatrix;
    this->inverseMatrix = this->transformMatrix;
    this->material = material;
    this->name = name;
}

void Mesh::parseFile(std::ifstream & file){
    std::string line;
    while(file){
        getline(file,line);
        if(line[0] == 'v' && line[1]==' '){
            parseV(line.substr(line.find(" ") + 1,line.length()));
        }
        else if(line[0] == 'v' && line[1]=='n'){
            parseN(line.substr(line.find(" ") + 1,line.length()));
        }
        else if (line[0] == 'v' && line[1] == 't'){
            parseT(line.substr(line.find(" ") + 1,line.length()));
        }
        else if(line[0] == 'f'){
            parseF(line.substr(line.find(" ") + 1,line.length()));
        }

    }
    file.close();
}

Triple<int,int,int> Mesh::parseFaceData(const std::string & line){
    Array<int> a;
    Triple<int,int,int> t;
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
    this->normalList.push(Vector3D(a.getElementAt(0),a.getElementAt(1),a.getElementAt(2)));
}

void Mesh::parseF(const std::string & line){

    std::string slashDelimiter = "/";
    std::string blankDelimiter = " ";
    std::string dataStr;
    std::string tempStr = line;
    Array<int> v;
    Array<int> t;
    Array<int> n;
    Triple<int,int,int> r;
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
    Face f = Face(v.getElementAt(0),v.getElementAt(1),v.getElementAt(2),n.getElementAt(0),t.getElementAt(0),t.getElementAt(1),t.getElementAt(2));
    this->faceList.push(f);
}

void Mesh::parseT(const std::string & line){
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
    this->uvList.push(UVTex(a.getElementAt(0),a.getElementAt(1)));
}

Material * Mesh::getMaterial(){
    return this->material;
}

std::string Mesh::getName(){
    return this->name;
}

void Mesh::transformView(Matrix<double,4,4> transformMatrix){
    for(int i = 0;i<this->vertexList.getSize();i++){
        this->vertexList.setElementAt(i,(transformMatrix*Matrix<double,4,1>(this->vertexList.getElementAt(i))).toVertex());
    }
    for(int j = 0;j<this->normalList.getSize();j++){
        this->normalList.setElementAt(j,(transformMatrix*Matrix<double,4,1>(this->normalList.getElementAt(j))).toVector3D());
    }
    this->stackedTranslateMatrix = stackedTranslateMatrix*transformMatrix ;
}

Vector3D Mesh::computeNormal(){
    return this->intersectedNormal;
}

double Mesh::IntersectRay(Coordinate O,Vector3D D,double t_min,double t_max){
    Coordinate V0, V1, V2;
    double b0,b1,b2,bFace;
    Plane plane;
    Face current_face;
    Vector3D N;
    double t_plane;
    double closest_t = INF;
    for(int i = 0;i<this->faceList.getSize();i++){
        current_face = this->faceList.getElementAt(i);
        N = this->normalList.getElementAt(current_face.n);
        V0 = Coordinate(this->vertexList.getElementAt(current_face.v1).x,this->vertexList.getElementAt(current_face.v1).y,this->vertexList.getElementAt(current_face.v1).z);
        V1 = Coordinate(this->vertexList.getElementAt(current_face.v2).x,this->vertexList.getElementAt(current_face.v2).y,this->vertexList.getElementAt(current_face.v2).z);
        V2 = Coordinate(this->vertexList.getElementAt(current_face.v3).x,this->vertexList.getElementAt(current_face.v3).y,this->vertexList.getElementAt(current_face.v3).z);
        
        plane = Plane(V1,N,nullptr);
        t_plane = plane.IntersectRay(O,D,t_min,t_max);
        
        if(t_plane < t_min || t_plane > t_max){
            continue;
        }
        
        Coordinate P = D*t_plane + O;
        Vector3D V1_V0 = Vector3D(V1-V0);
        Vector3D V2_V1 = Vector3D(V2-V1);
        Vector3D V0_V2 = Vector3D(V0-V2);
        Vector3D V2_V0 = Vector3D(V2-V0);
        Vector3D P_V0 = Vector3D(P-V0);
        Vector3D P_V1 = Vector3D(P-V1);
        Vector3D P_V2 = Vector3D(P-V2);
        
        b0 = Vector3D::dot(Vector3D::cross(V1_V0,P_V0),N);
        b1 = Vector3D::dot(Vector3D::cross(V2_V1,P_V1),N);
        b2 = Vector3D::dot(Vector3D::cross(V0_V2,P_V2),N);
        bFace = Vector3D::dot(Vector3D::cross(V1_V0,V2_V0),N);

        if(b0>=0 && b1>=0 && b2>=0 && t_plane<closest_t){
            current_face.faceArea = bFace;
            closest_t = t_plane;
            //confundi b com area, lembrar de arrumar.
            current_face.v1W = b1/bFace;
            current_face.v2W = b2/bFace;
            current_face.v3W = b0/bFace;
            
            //calcula faceArea
            this->intersectedFace = current_face;
            this->intersectedNormal = N;
        }   
    }
    return closest_t;
}

bool Mesh::setTransform(Transformation * t){
    //(this->transformList).push(t); 
    //this->stackedTransformMatrix = (this->stackedTransformMatrix)* t->getTransform();
    if(dynamic_cast<Translate *>(t)){
        stackedTranslateMatrix = stackedTranslateMatrix * t->getTransform();
    }

    this->transformMatrix = t->getTransform();
    this->inverseMatrix = t->getInverse();
    if(dynamic_cast<RotateXfixed*>(t) || dynamic_cast<RotateYfixed*>(t) || dynamic_cast<RotateZfixed*>(t)){
        applyTransform(t->getFixedPoint());
    }
    else{
        applyTransform();
    }


    
    return true;
    
}

void Mesh::applyTransform(Coordinate point){
    Matrix<double,4,4> transposeInverse = this->inverseMatrix.transpose();
    Vertex translateVertex = Vertex(-point.x,-point.y,-point.z);
    Vertex goBackVertex = Vertex(point.x,point.y,point.z);
    tempTransform(translateVertex); 
    for(int i=0;i<this->vertexList.getSize();i++){
        Vertex currentVertex = this->vertexList.getElementAt(i);
        Matrix<double,4,1> m = Matrix<double,4,1>(currentVertex);
        Matrix<double,4,1> transformedVertexMatrix = this->transformMatrix * m;
        Vertex newVertex = Vertex(transformedVertexMatrix.getVal(0,0),transformedVertexMatrix.getVal(1,0),transformedVertexMatrix.getVal(2,0));
        this->vertexList.setElementAt(i,newVertex);
    }
    tempTransform(goBackVertex); 
    for(int j = 0;j<this->normalList.getSize();j++){
        Vector4D currentNormal = Vector4D(this->normalList.getElementAt(j));
        Matrix<double,4,1> normalMatrix = Matrix<double,4,1>(currentNormal);
        Matrix<double,4,1> newNormal = transposeInverse * normalMatrix;
        Vector3D vecNormal = Vector3D(newNormal.getVal(0,0),newNormal.getVal(1,0),newNormal.getVal(2,0));
        vecNormal.normalize();
        normalList.setElementAt(j,vecNormal);
    }
    //reseting transforms
    this-> inverseMatrix = Matrix<double,4,4>::identity();
    this-> transformMatrix = Matrix<double,4,4>::identity();
    for(int k = 0;k<this->transformList.getSize();k++){
        //delete this->transformList.getElementAt(k);
        this->transformList.setElementAt(k,nullptr);

    }
}

void Mesh::applyTransform(){
    Matrix<double,4,4> transposeInverse = this->inverseMatrix.transpose();
    Vertex translateVertex = Vertex(stackedTranslateMatrix.getVal(0,3),stackedTranslateMatrix.getVal(1,3),stackedTranslateMatrix.getVal(2,3));
    Vertex goBackVertex = translateVertex*-1;
    
    tempTransform(translateVertex); 
    for(int i=0;i<this->vertexList.getSize();i++){
        Vertex currentVertex = this->vertexList.getElementAt(i);
        Matrix<double,4,1> m = Matrix<double,4,1>(currentVertex);
        Matrix<double,4,1> transformedVertexMatrix = this->transformMatrix * m;
        Vertex newVertex = Vertex(transformedVertexMatrix.getVal(0,0),transformedVertexMatrix.getVal(1,0),transformedVertexMatrix.getVal(2,0));
        this->vertexList.setElementAt(i,newVertex);
    }
    tempTransform(goBackVertex); 
    for(int j = 0;j<this->normalList.getSize();j++){
        Vector4D currentNormal = Vector4D(this->normalList.getElementAt(j));
        Matrix<double,4,1> normalMatrix = Matrix<double,4,1>(currentNormal);
        Matrix<double,4,1> newNormal = transposeInverse * normalMatrix;
        Vector3D vecNormal = Vector3D(newNormal.getVal(0,0),newNormal.getVal(1,0),newNormal.getVal(2,0));
        vecNormal.normalize();
        normalList.setElementAt(j,vecNormal);
    }
    //reseting transforms
    this-> inverseMatrix = Matrix<double,4,4>::identity();
    this-> transformMatrix = Matrix<double,4,4>::identity();
    for(int k = 0;k<this->transformList.getSize();k++){
        //delete this->transformList.getElementAt(k);
        this->transformList.setElementAt(k,nullptr);

    }
}

void Mesh::tempTransform(Vertex v){
    for(int i = 0;i<this->vertexList.getSize();i++){
        Vertex currentV = this->vertexList.getElementAt(i);
        this->vertexList.setElementAt(i,Vertex(currentV.x-v.x,currentV.y-v.y,currentV.z-v.z));
    }
}

bool Mesh::setTexture(const std::string & filePath,SDL_Renderer * renderer){
    this->texture = new Texture(filePath,renderer);
    return true;
}

Texture * Mesh::getTexture(){
    return this->texture;
}

Color Mesh::getTexel(Coordinate P,Coordinate O,Matrix<double,4,4> cameraToWorld){
    /*
    Matrix<double,4,1> Pmatrix = Matrix<double,4,1>(P);
    //Matrix<double,4,1> Omatrix = Matrix<double,4,1>(O);
    P = (cameraToWorld*Pmatrix).toCoordinate();
    //O = (cameraToWorld*Omatrix).toCoordinate();
    Vector3D N = (cameraToWorld * Matrix<double,4,1>(this->normalList.getElementAt(intersectedFace.n))).toVector3D();
    Coordinate V0 =  (cameraToWorld * Matrix<double,4,1>(this->vertexList.getElementAt(intersectedFace.v1))).toCoordinate();
    Coordinate V1 = (cameraToWorld * Matrix<double,4,1>(this->vertexList.getElementAt(intersectedFace.v2))).toCoordinate();
    Coordinate V2 = (cameraToWorld * Matrix<double,4,1>(this->vertexList.getElementAt(intersectedFace.v3))).toCoordinate();
    Vector3D V1_V0 = Vector3D(V1-V0);
    Vector3D V2_V1 = Vector3D(V2-V1);
    Vector3D V0_V2 = Vector3D(V0-V2);
    Vector3D P_V0 = Vector3D(P-V0);
    Vector3D P_V1 = Vector3D(P-V1);
    Vector3D P_V2 = Vector3D(P-V2);
    */
    if(!this->texture){
        return Color();
    }
    
    UVTex v1tex = this->uvList.getElementAt(this->intersectedFace.v1t);
    UVTex v2tex = this->uvList.getElementAt(this->intersectedFace.v2t);
    UVTex v3tex = this->uvList.getElementAt(this->intersectedFace.v3t);
    
    double u = v1tex.u * this->intersectedFace.v1W + v2tex.u * this->intersectedFace.v2W + v3tex.u * this->intersectedFace.v3W;
    double v = v1tex.v * this->intersectedFace.v1W + v2tex.v * this->intersectedFace.v2W + v3tex.v * this->intersectedFace.v3W;   
    Pair<int,int> wh = this->texture->getWH();

    Color c = this->texture->getColorAt( abs((int)(floor(u * wh.left) )),abs((int)floor( v* wh.right)));
    return c;
  


}