#ifndef LIGHT_H
#define LIGHT_H

#include "Coordinate.h"
#include "Vector.h"


class Light{
    public:
        Light();
        float getIntensity();
        bool setIntensity(float);
        float calcIntensity(Coordinate, Vector);
        
    private:
        
        float intensity = 1.0;

};

class AmbientLight : public Light{
    public:
        AmbientLight();
        AmbientLight(float intensity);
        float calcIntensity(Coordinate, Vector);
    private:
        float intensity;
};

class DirectionalLight : public Light{
    public:

        DirectionalLight();
        DirectionalLight(float intensity,Vector direction);
        float calcIntensity(Coordinate, Vector);
        Vector getDirection();
        bool setDirection(Vector);
    private:
        Vector direction;
        float intensity;
};  

class PointLight : public Light{
    public:
        PointLight();
        PointLight(float intensity, Coordinate position);
        float calcIntensity(Coordinate, Vector);
        Coordinate getPosition();
        bool setPosition(Coordinate);
    private:
        Coordinate position;
        float intensity;    
};

#endif