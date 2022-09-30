#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdio.h>
#include "../Ilumination/Reflect.h"


struct Material{
    private:
        AmbientReflectiveness ka;
        DifuseReflectiveness kd;
        SpecularReflectiveness ke;
    public:
        virtual AmbientReflectiveness getKa()=0;
        virtual DifuseReflectiveness getKd()=0;
        virtual SpecularReflectiveness getKe()=0;


};

struct Rubber : Material{
    public:
    Rubber() : ka(AmbientReflectiveness(Coeficients{1,1,1})),kd(DifuseReflectiveness(Coeficients(1,0,0))),ke(SpecularReflectiveness(Coeficients(0.5,0,0),500)){};

    AmbientReflectiveness getKa();
    DifuseReflectiveness getKd();
    SpecularReflectiveness getKe();
    private:
    AmbientReflectiveness ka;
    DifuseReflectiveness kd;
    SpecularReflectiveness ke;
};

#endif

