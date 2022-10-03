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
