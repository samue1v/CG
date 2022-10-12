#include <stdio.h>
#include "Material.h"

AmbientReflectiveness Rubber::getKa(){
    return this->ka;
}

DifuseReflectiveness Rubber::getKd(){
    return this->kd;
}

SpecularReflectiveness Rubber::getKe(){
    return this->ke;
}

AmbientReflectiveness Metal::getKa(){
    return this->ka;
}

DifuseReflectiveness Metal::getKd(){
    return this->kd;
}

SpecularReflectiveness Metal::getKe(){
    return this->ke;
}
AmbientReflectiveness Plastic::getKa(){
    return this->ka;
}

DifuseReflectiveness Plastic::getKd(){
    return this->kd;
}

SpecularReflectiveness Plastic::getKe(){
    return this->ke;
}
AmbientReflectiveness Cooper::getKa(){
    return this->ka;
}

DifuseReflectiveness Cooper::getKd(){
    return this->kd;
}

SpecularReflectiveness Cooper::getKe(){
    return this->ke;
}