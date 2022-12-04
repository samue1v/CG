#ifndef CAMERA_H
#define CAMERA_H
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/Matrix.h"
class Camera{
    private:
    Coordinate lookAt;
    Coordinate up;
    Coordinate eye;
    Coordinate eyeTransformed;
    Matrix<double,4,4> worldToCamera;
    Matrix<double,4,4> cameraToWorld;
    public:
    Camera();
    Camera(Coordinate eye,Coordinate lookAt,Coordinate up);
    bool setLookAt(Coordinate newLookAt);
    bool setEye(Coordinate newEye);
    bool setUp(Coordinate newUp);
    Matrix<double,4,4> getWorldToCamera();
    Matrix<double,4,4> getCameraToWorld();
    Coordinate getEyeTransformed();
    Coordinate getEye();
    Coordinate getUp();
    Coordinate getLookAt();
    void calcTransforms();
    

};

#endif