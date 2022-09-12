#ifndef LIGHT_H
#define LIGHT_H

#include "Coordinate.h"
#include "Vector.h"


class Light{
    public:
        Light();
        virtual float getIntensity() = 0;
        virtual bool setIntensity(float) = 0;
        virtual float calcIntensity(Coordinate, Vector)=0;
        
    private:
        
        float intensity = 1.0;

};

class AmbientLight : public Light{
    public:
        AmbientLight();
        AmbientLight(float intensity);
        float getIntensity();
        bool setIntensity(float newIntensity);
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
        float getIntensity();
        bool setIntensity(float newIntensity);
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
        float getIntensity();
        bool setIntensity(float newIntensity);
    private:
        Coordinate position;
        float intensity;    
};

#endif