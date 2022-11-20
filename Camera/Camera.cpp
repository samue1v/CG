#include <stdio.h>
#include "Camera.h"
#include "DataStructures/Vector.h"

Camera::Camera(){
    this->eye = Coordinate(0,0,0);
    this->lookAt = Coordinate(0,0,-1);
    this->up = Coordinate(0,1,0);
    calcTransform();

}

Camera::Camera(Coordinate eye,Coordinate lookAt,Coordinate up) : eye(eye),lookAt(lookAt),up(up){
    calcTransform();
}

bool Camera::setEye(Coordinate newEye){
    this->eye = newEye;     
    return true;
}

bool Camera::setLookAt(Coordinate newLookAt){
    this->lookAt = newLookAt;
    return true;
}

bool Camera::setUp(Coordinate newUp){
    this->up = newUp;
    return true;
}

Coordinate Camera::transformCoordinate(Coordinate coord){
    Matrix<double,1,4> m = Matrix<double,1,4>(coord);
    m = m*transformMatrix;
    return m.toCoordinate();

}

void Camera::calcTransform(){
    Vector4D k = Vector4D(eye - lookAt);
    k.normalize();
    Vector4D upVec = Vector4D(up - eye);
    Vector4D i = Vector4D::cross(upVec,k);
    i.normalize();
    Vector4D j = Vector4D::cross(k,i);
    j.normalize();
    transformMatrix.setVal(0,0,i.getElementAt(0));
    transformMatrix.setVal(0,1,i.getElementAt(1));
    transformMatrix.setVal(0,2,i.getElementAt(2));

    transformMatrix.setVal(1,0,j.getElementAt(0));
    transformMatrix.setVal(1,1,j.getElementAt(1));
    transformMatrix.setVal(1,2,j.getElementAt(2));

    transformMatrix.setVal(2,0,k.getElementAt(0));
    transformMatrix.setVal(2,1,k.getElementAt(1));
    transformMatrix.setVal(2,2,k.getElementAt(2));

    transformMatrix.setVal(3,3,1);
}