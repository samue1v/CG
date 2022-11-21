#ifndef CAMERA_H
#define CAMERA_H
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/Matrix.h"
class Camera{
    private:
    Coordinate lookAt;
    Coordinate up;
    Coordinate eye;
    Matrix<double,4,4> transformMatrix;
    public:
    Camera();
    Camera(Coordinate eye,Coordinate lookAt,Coordinate up);
    bool setLookAt(Coordinate newLookAt);
    bool setEye(Coordinate newEye);
    bool setUp(Coordinate newUp);
    Matrix<double,4,4> getTransformMatrix();
    Coordinate getEye();
    Coordinate getUp();
    Coordinate getLookAt();
    Coordinate transformCoordinate(Coordinate coord);
    void calcTransform();
    

};

#endif