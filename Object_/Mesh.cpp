#include "Mesh.h"
#include "../DataStructures/MeshUtils.h"
#include "../DataStructures/Triple.h"
#include "../DataStructures/Vector.h"
#include <string>
#include <iostream>

Mesh::Mesh(){}

Mesh::Mesh(const std::string & filePath){
    this->file.open(filePath);
    parseFile();
}

void Mesh::parseFile(){
    std::string line;
    while(this->file){
        getline(this->file,line);
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
    this->file.close();
}

Triple<int> Mesh::parseData(const std::string & line){
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
        r = parseData(dataStr);
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
