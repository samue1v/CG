#ifndef LIGHT_H
#define LIGHT_H

#include "Coordinate.h"
#include "Vector.h"


class Light{
    public:
        float getIntensity();
        bool setIntensity(float);

        virtual float calcIntensity(Coordinate, Vector);

    private:
        
        float intensity = 0;

};

class AmbientLight : private Light{
    public:
        virtual float calcIntensity(Coordinate, Vector);
        Coordinate getPosition();
        bool setPosition(Coordinate);
    private:
        Coordinate position;
};

class DirectionalLight : private Light{
    public:
        virtual float calcIntensity(Coordinate, Vector);
        Coordinate getDirection();
        bool setDirection(Coordinate);
    private:
        Vector direction;
};  

class PointLight : private Light{
    public:
        virtual float calcIntensity(Coordinate, Vector);
};

#endif