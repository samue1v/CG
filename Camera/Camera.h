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
    Camera(Coordinate eye,Coordinate lookAt,Coodinate up);
    bool setLookAt(Coordinate newLookAt);
    bool setEye(Coordiante newEye);
    bool setUp(Coordinate newUp);
    Coordinate transformCoordinate(Coordinate coord);
    void calcTransform();

};

#endif