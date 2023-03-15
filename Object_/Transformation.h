#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <iostream>
#include "../DataStructures/Matrix.h"
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include <math.h>

enum TransformType{
  translate = 0,
  scale = 1,
  rotatex = 2,
  rotatey = 3,
  rotatez = 4,
  rotatexfixed = 5,
  rotateyfixed = 6,
  rotatezfixed = 7,
  shearxy = 8,
  shearyx = 9,
  shearxz = 10,
  shearzx = 11,
  shearyz = 12,
  shearzy = 13,
};

struct Transformation{
    
    Transformation(){}
    virtual Matrix<float,4,4> getTransform() = 0;
    virtual Matrix<float,4,4> getInverse() = 0;
    virtual Coordinate getFixedPoint() = 0;
    TransformType getType(){
        return this->transformType;
    }
    protected:
    TransformType transformType;
    Coordinate fixedPoint;
    Matrix<float,4,4> transform;
    Matrix<float,4,4> inverse;
};

struct Translate : public Transformation{
    Translate(){}
    Translate(float x, float y, float z){
        this->transform = Matrix<float,4,4>::identity();
        (this->transform).setVal(0,3,x);
        (this->transform).setVal(1,3,y);
        (this->transform).setVal(2,3,z);
        this->inverse = this->transform;
        (this->inverse).setVal(0,3,-x);
        (this->inverse).setVal(1,3,-y);
        (this->inverse).setVal(2,3,-z);
        this->transformType = translate;
    }
    
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
    
};


struct RotateX : public Transformation{
    RotateX(){}
    RotateX(float angle){
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float cosine = cos(radiansAngle);
        float sine = sin(radiansAngle);
        (this->transform).setVal(1,1,cosine);
        (this->transform).setVal(2,2,cosine);
        (this->transform).setVal(1,2,-sine);
        (this->transform).setVal(2,1,sine);
        this->inverse = this->transform.transpose();
        this->transformType = rotatex;
    

    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct RotateY : public Transformation{
    RotateY(){}
    RotateY(float angle){
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float cosine = cos(radiansAngle);
        float sine = sin(radiansAngle);
        (this->transform).setVal(0,0,cosine);
        (this->transform).setVal(0,2,sine);
        (this->transform).setVal(2,0,-sine);
        (this->transform).setVal(2,2,cosine);
        this->inverse = this->transform.transpose();
        this->transformType = rotatey;
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct RotateZ : public Transformation{
    RotateZ(){}
    RotateZ(float angle){
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float cosine = cos(radiansAngle);
        float sine = sin(radiansAngle);
        (this->transform).setVal(0,0,cosine);
        (this->transform).setVal(1,0,sine);
        (this->transform).setVal(0,1,-sine);
        (this->transform).setVal(1,1,cosine);
        this->inverse = this->transform.transpose();
        this->transformType = rotatez;
    }

    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct RotateXfixed : public Transformation{
    RotateXfixed(){}
    RotateXfixed(float angle,Coordinate point){
        this->fixedPoint;
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float cosine = cos(radiansAngle);
        float sine = sin(radiansAngle);
        (this->transform).setVal(1,1,cosine);
        (this->transform).setVal(2,2,cosine);
        (this->transform).setVal(1,2,-sine);
        (this->transform).setVal(2,1,sine);
        this->inverse = this->transform.transpose();
        this->transformType = rotatexfixed;

    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct RotateYfixed : public Transformation{
    RotateYfixed(){}
    RotateYfixed(float angle,Coordinate point){
        this->fixedPoint = point;
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float cosine = cos(radiansAngle);
        float sine = sin(radiansAngle);
        (this->transform).setVal(0,0,cosine);
        (this->transform).setVal(0,2,sine);
        (this->transform).setVal(2,0,-sine);
        (this->transform).setVal(2,2,cosine);
        this->inverse = this->transform.transpose();
        this->transformType = rotateyfixed;
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct RotateZfixed : public Transformation{
    RotateZfixed(){}
    RotateZfixed(float angle,Coordinate point){
        this->fixedPoint = point;
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float cosine = cos(radiansAngle);
        float sine = sin(radiansAngle);
        (this->transform).setVal(0,0,cosine);
        (this->transform).setVal(1,0,sine);
        (this->transform).setVal(0,1,-sine);
        (this->transform).setVal(1,1,cosine);
        this->inverse = this->transform.transpose();
        this->transformType = rotatezfixed;
        
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};


struct Scale : public Transformation{
    Scale(){}
    Scale(float x,float y,float z){
        this->transform = Matrix<float,4,4>::identity();
        this->inverse = this->transform;
        (this->transform).setVal(0,0,x);
        (this->transform).setVal(1,1,y);
        (this->transform).setVal(2,2,z);
        (this->inverse).setVal(0,0,1.0/x);
        (this->inverse).setVal(1,1,1.0/y);
        (this->inverse).setVal(2,2,1.0/z);
        this->transformType = scale;
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct ReflectXY : public Transformation{
    ReflectXY(){
        this->transform = Matrix<float,4,4>::identity();
        (this->transform).setVal(2,2,-1);
        this->inverse = this->transform;

    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct ReflectXZ : public Transformation{
    ReflectXZ(){
        this->transform = Matrix<float,4,4>::identity();
        (this->transform).setVal(1,1,-1);
        this->inverse = this->transform;

    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct ReflectYZ : public Transformation{
    ReflectYZ(){
        this->transform = Matrix<float,4,4>::identity();
        (this->transform).setVal(0,0,-1);
        this->inverse = this->transform;

    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct ShearXY : public Transformation{
    ShearXY(){}
    ShearXY(float angle){
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float tangent = tan(radiansAngle);
        (this->transform).setVal(1,0,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(1,0,-tangent);
        this->transformType = shearxy;
    
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct ShearYX : public Transformation{
    ShearYX(){}
    ShearYX(float angle){
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float tangent = tan(radiansAngle);
        (this->transform).setVal(0,1,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(0,1,-tangent);
        this->transformType = shearyx;
    
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct ShearXZ : public Transformation{
    ShearXZ(){}
    ShearXZ(float angle){
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float tangent = tan(radiansAngle);
        (this->transform).setVal(2,0,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(2,0,-tangent);
        this->transformType = shearxz;
    
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct ShearZX : public Transformation{
    ShearZX(){}
    ShearZX(float angle){
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float tangent = tan(radiansAngle);
        (this->transform).setVal(0,2,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(0,2,-tangent);
        this->transformType = shearzx;
    
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct ShearYZ : public Transformation{
    ShearYZ(){}
    ShearYZ(float angle){
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float tangent = tan(radiansAngle);
        (this->transform).setVal(2,1,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(2,1,-tangent);
        this->transformType = shearyz;
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};

struct ShearZY : public Transformation{
    ShearZY(){}
    ShearZY(float angle){
        this->transform = Matrix<float,4,4>::identity();
        float radiansAngle = (angle*PI)/180.0;
        float tangent = tan(radiansAngle);
        (this->transform).setVal(1,2,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(1,2,-tangent);
        this->transformType = shearzy;
    }
    Matrix<float,4,4> getTransform(){
        return this->transform;
    }
    Matrix<float,4,4> getInverse(){
        return this->inverse;
    }
    Coordinate getFixedPoint(){
        return this->fixedPoint;
    }
};
#endif