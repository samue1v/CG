#include <stdio.h>
#include "ds.h"
#include "polygons.cpp"

class Scene{
    public:
        Scene(int numPolygons);
        Polygon * getPolygonAt(int index); //olhar depois
        bool setPolygon(int index, Polygon polygon);
        Polygon * getPolygonArray();
        int getNumberOfElements();
        bool setBackgroundColor(Color color);
        Color getBackgroundColor();
    private:
        Color backgroud_color;
        int numPolygons; 
        Polygon * elements;
        
};

Scene::Scene(int numPolygons){
    Polygon * p;
    Polygon * polygonsArray[numPolygons];
    this->numPolygons = numPolygons;
    this->elements = *polygonsArray;
} 
Polygon * Scene::getPolygonAt(int index){
    Polygon * p = &(this->elements)[index]; //ver qual a maneira correta
    return p;
}
Polygon * Scene::getPolygonArray(){
    Polygon * p = this->elements;
    return p;
}

bool Scene::setPolygon(int index,Polygon polygon){
    if(index >=numPolygons || index<0){
        return false;
    }
    this->elements[index] = polygon;
}

int Scene::getNumberOfElements(){
    return this->numPolygons;
}

bool Scene::setBackgroundColor(Color color){
    if(color.red>255 || color.red<0 || color.green>255 || color.green<0 || color.blue<0 || color.blue>255){
        return false;
    }
    this->backgroud_color = color;
}