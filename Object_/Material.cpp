#include <stdio.h>
#include "Material.h"

AmbientReflectiveness Material::getKa(){
    return this->ka;
}

DifuseReflectiveness Material::getKd(){
    return this->kd;
}

SpecularReflectiveness Material::getKe(){
    return this->ke;
}

bool Material::setKa(AmbientReflectiveness newKa){
    this->ka = newKa;
    return true;
}

bool Material::setKd(DifuseReflectiveness newKd){
    this->kd = newKd;
    return true;
}

bool Material::setKe(SpecularReflectiveness newKe){
    this->ke = newKe;
    return true;
}

std::string Material::getName(){
    return name;
}