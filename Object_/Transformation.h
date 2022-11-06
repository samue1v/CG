#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <iostream>
#include "../DataStructures/Matrix.h"
#include "../DataStructures/DataConsts.h"
#include <math.h>
struct Transformation{
    
    Transformation(){}
    virtual Matrix<double,4,4> getTransform() = 0;
    virtual Matrix<double,4,4> getInverse() = 0;
    protected:
    Matrix<double,4,4> transform;
    Matrix<double,4,4> inverse;
};

struct Translate : public Transformation{
    Translate(){}
    Translate(double x, double y, double z){
        this->transform = Matrix<double,4,4>::identity();
        (this->transform).setVal(0,3,x);
        (this->transform).setVal(1,3,y);
        (this->transform).setVal(2,3,z);
        this->inverse = this->transform;
        (this->inverse).setVal(0,3,-x);
        (this->inverse).setVal(1,3,-y);
        (this->inverse).setVal(2,3,-z);
        
    }
    
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
    
};


struct RotateX : public Transformation{
    RotateX(){}
    RotateX(double angle){
        this->transform = Matrix<double,4,4>::identity();
        double radiansAngle = (angle*PI)/180.0;
        double cosine = cos(radiansAngle);
        double sine = sin(radiansAngle);
        (this->transform).setVal(1,1,cosine);
        (this->transform).setVal(2,2,cosine);
        (this->transform).setVal(1,2,-sine);
        (this->transform).setVal(2,1,sine);
        this->inverse = this->transform.transpose();

    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct RotateY : public Transformation{
    RotateY(){}
    RotateY(double angle){
        this->transform = Matrix<double,4,4>::identity();
        double radiansAngle = (angle*PI)/180.0;
        double cosine = cos(radiansAngle);
        double sine = sin(radiansAngle);
        (this->transform).setVal(0,0,cosine);
        (this->transform).setVal(0,2,sine);
        (this->transform).setVal(2,0,-sine);
        (this->transform).setVal(2,2,cosine);
        this->inverse = this->transform.transpose();
    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct RotateZ : public Transformation{
    RotateZ(){}
    RotateZ(double angle){
        this->transform = Matrix<double,4,4>::identity();
        double radiansAngle = (angle*PI)/180.0;
        double cosine = cos(radiansAngle);
        double sine = sin(radiansAngle);
        (this->transform).setVal(0,0,cosine);
        (this->transform).setVal(1,0,sine);
        (this->transform).setVal(0,1,-sine);
        (this->transform).setVal(1,1,cosine);
        this->inverse = this->transform.transpose();
        
    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct Scale : public Transformation{
    Scale(){}
    Scale(double x,double y,double z){
        this->transform = Matrix<double,4,4>::identity();
        this->inverse = this->transform;
        (this->transform).setVal(0,0,x);
        (this->transform).setVal(1,1,y);
        (this->transform).setVal(2,2,z);
        (this->inverse).setVal(0,0,1.0/x);
        (this->inverse).setVal(1,1,1.0/y);
        (this->inverse).setVal(2,2,1.0/z);
    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct ReflectXY : public Transformation{
    ReflectXY(){
        this->transform = Matrix<double,4,4>::identity();
        (this->transform).setVal(2,2,-1);
        this->inverse = this->transform;

    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct ReflectXZ : public Transformation{
    ReflectXZ(){
        this->transform = Matrix<double,4,4>::identity();
        (this->transform).setVal(1,1,-1);
        this->inverse = this->transform;

    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct ReflectYZ : public Transformation{
    ReflectYZ(){
        this->transform = Matrix<double,4,4>::identity();
        (this->transform).setVal(0,0,-1);
        this->inverse = this->transform;

    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct ShearXY : public Transformation{
    ShearXY(){}
    ShearXY(double angle){
        this->transform = Matrix<double,4,4>::identity();
        double radiansAngle = (angle*PI)/180.0;
        double tangent = tan(radiansAngle);
        (this->transform).setVal(1,0,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(1,0,-tangent);
    
    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct ShearYX : public Transformation{
    ShearYX(){}
    ShearYX(double angle){
        this->transform = Matrix<double,4,4>::identity();
        double radiansAngle = (angle*PI)/180.0;
        double tangent = tan(radiansAngle);
        (this->transform).setVal(0,1,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(0,1,-tangent);
    
    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct ShearXZ : public Transformation{
    ShearXZ(){}
    ShearXZ(double angle){
        this->transform = Matrix<double,4,4>::identity();
        double radiansAngle = (angle*PI)/180.0;
        double tangent = tan(radiansAngle);
        (this->transform).setVal(2,0,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(2,0,-tangent);
    
    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct ShearZX : public Transformation{
    ShearZX(){}
    ShearZX(double angle){
        this->transform = Matrix<double,4,4>::identity();
        double radiansAngle = (angle*PI)/180.0;
        double tangent = tan(radiansAngle);
        (this->transform).setVal(0,2,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(0,2,-tangent);
    
    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct ShearYZ : public Transformation{
    ShearYZ(){}
    ShearYZ(double angle){
        this->transform = Matrix<double,4,4>::identity();
        double radiansAngle = (angle*PI)/180.0;
        double tangent = tan(radiansAngle);
        (this->transform).setVal(2,1,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(2,1,-tangent);
    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};

struct ShearZY : public Transformation{
    ShearZY(){}
    ShearZY(double angle){
        this->transform = Matrix<double,4,4>::identity();
        double radiansAngle = (angle*PI)/180.0;
        double tangent = tan(radiansAngle);
        (this->transform).setVal(1,2,tangent);
        this->inverse = this->transform;
        (this->inverse).setVal(1,2,-tangent);
    }
    Matrix<double,4,4> getTransform(){
        return this->transform;
    }
    Matrix<double,4,4> getInverse(){
        return this->inverse;
    }
};
#endif