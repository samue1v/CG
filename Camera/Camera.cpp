#include <stdio.h>
#include "Camera.h"
#include <iostream>
#include "../DataStructures/Vector.h"
#include "../DataStructures/Coordinate.h"

Camera::Camera(){
    this->eye = Coordinate(0,0,0);
    this->lookAt = Coordinate(0,0,-1);
    this->up = Coordinate(0,1,0);
    k = Vector3D(eye - lookAt);
    k.normalize();
    Vector3D upVec = Vector3D(up - eye);
    i = Vector3D::cross(upVec,k);
    i.normalize();
    j = Vector3D::cross(k,i);
    j.normalize();
    execEyeTransform();

}

Camera::Camera(Coordinate eye,Coordinate lookAt,Coordinate up){
    this->eye = eye;
    this->up = up;
    this->lookAt = lookAt;
    k = Vector3D(eye - lookAt);
    k.normalize();
    Vector3D upVec = Vector3D(up - eye);
    i = Vector3D::cross(upVec,k);
    i.normalize();
    j = Vector3D::cross(k,i);
    j.normalize();
    execEyeTransform();
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

Coordinate Camera::getEye(){
    return eye;
}

Coordinate Camera::getLookAt(){
    return lookAt;
}

Coordinate Camera::getUp(){
    return up;
}

Matrix<double,4,4> Camera::getWorldToCamera(){
    return this->worldToCamera;
}

Matrix<double,4,4> Camera::getCameraToWorld(){
    return this->cameraToWorld;
}

Coordinate Camera::getEyeTransformed(){
    return eyeTransformed;
}

void Camera::setTransform(Transformation * t){

    if(t->getType() == translate){
        this->eye = (t->getTransform()*Matrix<double,4,1>(this->eye)).toCoordinate();
        this->lookAt = (t->getTransform()*Matrix<double,4,1>(this->lookAt)).toCoordinate();
        this->up = (t->getTransform()*Matrix<double,4,1>(this->up)).toCoordinate();
    }

    else{
        this->i = (t->getTransform()*Matrix<double,4,1>(this->i)).toVector3D();
        this->j = (t->getTransform()*Matrix<double,4,1>(this->j)).toVector3D();
        this->k = (t->getTransform()*Matrix<double,4,1>(this->k)).toVector3D();

    }
    

    
}

void Camera::execEyeTransform(){

    worldToCamera.setVal(0,0,i.getElementAt(0));
    worldToCamera.setVal(0,1,i.getElementAt(1));
    worldToCamera.setVal(0,2,i.getElementAt(2));
    worldToCamera.setVal(0,3,-Vector4D::dot(eye,i));

    worldToCamera.setVal(1,0,j.getElementAt(0));
    worldToCamera.setVal(1,1,j.getElementAt(1));
    worldToCamera.setVal(1,2,j.getElementAt(2));
    worldToCamera.setVal(1,3,-Vector4D::dot(eye,j));

    worldToCamera.setVal(2,0,k.getElementAt(0));
    worldToCamera.setVal(2,1,k.getElementAt(1));
    worldToCamera.setVal(2,2,k.getElementAt(2));
    worldToCamera.setVal(2,3,-Vector4D::dot(eye,k));

    worldToCamera.setVal(3,3,1);

    cameraToWorld.setVal(0,0,i.getElementAt(0));
    cameraToWorld.setVal(0,1,j.getElementAt(0));
    cameraToWorld.setVal(0,2,k.getElementAt(0));
    cameraToWorld.setVal(0,3,eye.x);

    cameraToWorld.setVal(1,0,i.getElementAt(1));
    cameraToWorld.setVal(1,1,j.getElementAt(1));
    cameraToWorld.setVal(1,2,k.getElementAt(1));
    cameraToWorld.setVal(1,3,eye.y);

    cameraToWorld.setVal(2,0,i.getElementAt(2));
    cameraToWorld.setVal(2,1,j.getElementAt(2));
    cameraToWorld.setVal(2,2,k.getElementAt(2));
    cameraToWorld.setVal(2,3,eye.z);

    cameraToWorld.setVal(3,3,1);

    Matrix<double,4,4> mtc = worldToCamera * cameraToWorld;
    std::cout<<mtc;
    //worldToCamera = worldToCamera.transpose();
    Matrix<double,4,1> eyematrix = Matrix<double,4,1>(eye);
    //Matrix<double,4,4> cameraMatrix = camera->getWorldToCamera();
    Matrix<double,4,1> tmatrix = worldToCamera*eyematrix;
    this->eyeTransformed = (tmatrix).toCoordinate();
    //this->eyeTransformed = eye;
}