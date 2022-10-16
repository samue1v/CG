
#include "Shapes.h"
#include <iostream>
#include <stdio.h>

Shape3D::Shape3D() {}

Sphere::Sphere(Coordinate center, double radius, Material *material)
    : Shape3D() {
  this->center = center;
  this->radius = radius;
  this->material = (material);
}

bool Sphere::setCenter(Coordinate newCenter) {
  this->center = newCenter;
  return true;
}

Coordinate Sphere::getCenter() { return this->center; }

bool Sphere::setRadius(double newRadius) {
  if (newRadius > 0) {
    this->radius = newRadius;
    return true;
  }
  return false;
}

double Sphere::getRadius() { return this->radius; }

bool Sphere::setMaterial(Material *material) {
  this->material = material;
  return true;
}

double Sphere::IntersectRay(Coordinate O, Vector D,double tMin,double tMax) {
  double r = this->getRadius();
  Vector c_minus_o = Vector((O - this->getCenter()));
  double a = Vector::dot(D, D);
  double b = 2 * Vector::dot(c_minus_o, D);
  double c = Vector::dot(c_minus_o, c_minus_o) - r * r;

  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return INF;
  }

  double t1 = (-b + sqrt(discriminant)) / (2 * a);
  double t2 = (-b - sqrt(discriminant)) / (2 * a);

  if(t1>=tMin && t1<=tMax && t1<t2){
    return t1;
  }
  return t2;
}

Material *Sphere::getMaterial() { return (this->material); }

Vector Sphere::computeNormal(Coordinate P,Vector D) {
  return Vector(P - (this->center));
}

Plane::Plane() {}

Plane::Plane(Coordinate planePoint, Vector normal, Material * material) {
  this->planePoint = planePoint;
  this->normal = normal;
  this->material = material;
}

Material *Plane::getMaterial() { return this->material; }

Vector Plane::computeNormal(Coordinate P,Vector D){ return this->normal;}

double Plane::IntersectRay(Coordinate O, Vector D,double tMin,double tMax){
  Vector p_minuspi = Vector(this->planePoint - O);//mudei aqui
  double denom = Vector::dot(D,this->normal);
    double t = Vector::dot(p_minuspi,this->normal) / denom;
    if(t>=tMin && t<tMax){
  	 return t;
    }
	return INF;
}

Cylinder::Cylinder(){}

Cylinder::Cylinder(Coordinate baseCenter, Vector axis, double radius, double height,Material * material)
: baseCenter(baseCenter),  axis(axis), radius(radius), height(height){

  this->material = material;
  this->topCenter = (axis*height) + baseCenter;
  this->baseLid = Plane(baseCenter,axis*-1,new Cooper());
  this->topLid = Plane(topCenter,axis,new Cooper());
}

Material * Cylinder::getMaterial(){
  return this->material;
}

Vector Cylinder::computeNormal(Coordinate P,Vector D){


  if(this->intersectSurf == BOT){
    return this->baseLid.computeNormal(P,D);
  }
  else if(this->intersectSurf == TOP){
    return this->topLid.computeNormal(P,D);
  }


  /*
  Vector n = (*(this->M) * Matrix<double>(P - this->baseCenter))->toVector();
  n.normalize();
  */
  Vector V = Vector(P - this->baseCenter);
  double lv = V.getLength();
  double pll = sqrt(lv*lv - (this->radius*this->radius));
  Coordinate Pl = ((this->axis) * pll) + this->baseCenter;
  Vector N = Vector(P-Pl);
  N.normalize();

  return N;
}

double Cylinder::IntersectRay(Coordinate O, Vector D, double tMin, double tMax){
  double a,b,c;
  double delta;
  double closest_t = INF;
  double t1, t2;
  double tBase;
  double tTop;
  Vector w = Vector(O-this->baseCenter);
  a = 1-(Vector::dot(D,this->axis)*Vector::dot(D,this->axis));
  b = 2*(Vector::dot(w,D) - (Vector::dot(w,this->axis) * Vector::dot(D,this->axis)));
  c = Vector::dot(w,w) - (Vector::dot(w,this->axis)*Vector::dot(w,this->axis)) - (this->radius * this->radius);
  delta = (b*b) - (4*a*c);
  if(delta<0){
    return closest_t;
  }
  t1 = (-b + std::sqrt(delta)) / (2*a);
  t2 = (-b - std::sqrt(delta)) / (2*a);

  tBase = this->baseLid.IntersectRay(O,D,1,INF);
  tTop = this->topLid.IntersectRay(O,D,1,INF);

  Coordinate pi;
  if(tBase >1 && tBase<INF){
    pi = (D * tBase) + O;
    double baseTest = Vector(pi - this->baseCenter).getLength();
    if(baseTest > 0 && baseTest < this->radius){
      closest_t = tBase;
      intersectSurf = BOT;
    }
  }

  if(tTop >1 && tTop<INF){
    pi = (D * tTop) + O;
    double topTest = Vector(pi - this->topCenter).getLength();
    if(topTest > 0 && topTest < this->radius){
      if(closest_t > tTop){
        closest_t = tTop;
        intersectSurf = TOP;
      }
    }
  }

  Vector piSurf1 = Vector((D*t1 +O) - this->baseCenter);
  Vector piSurf2 = Vector((D*t2 +O) - this->baseCenter);

  double surfT1 = Vector::dot(piSurf1,this->axis);
  double surfT2 = Vector::dot(piSurf2,this->axis);
  double surfClosest_t;
  if(surfT1 > 0 && surfT1 <= this->height){
    if(t1 > 0 && t1<closest_t){
      closest_t = t1;
      this->intersectSurf = SURF;
    }
  }


  if(surfT2 > 0 && surfT2 <= this->height){
    if(t2 > 0 && t2< closest_t){
      closest_t = t2;
      this->intersectSurf = SURF;
    }
  }

  return closest_t;
}

Cone::Cone(){}

Cone::Cone(Coordinate baseCenter,Vector axis,double radius,double height,Material * material) : baseCenter(baseCenter),axis(axis),radius(radius),height(height){
  this->material = material;
  this->cosTeta = this->height /(sqrt(radius*radius + height*height));
  this->vertex = (axis*height)+baseCenter;
  this->baseLid = Plane(baseCenter,axis*-1,new Cooper());

}

Material * Cone::getMaterial(){
  return this->material;
}

Vector Cone::computeNormal(Coordinate P,Vector D){
  Vector pv = Vector(this->vertex - P);
  double xvLength = pv.getLength()/this->cosTeta; 
  Coordinate x = (this->axis*(this->height-xvLength)) + this->baseCenter;
  Vector n = Vector(P - x);
  n.normalize();
  return n;
}

double Cone::IntersectRay(Coordinate O, Vector D, double tMin, double tMax){
  double a, b, c, t1, t2;
  double delta;
  double beta;
  double tBase;
  double closest_t = INF;
  
  Matrix<double,3,1> dr = Matrix<double,3,1>(D);
  Matrix<double,3,1> dc = Matrix<double,3,1>(this->axis);
  Vector wv = Vector(this->vertex - O);
  beta = ((this->radius*this->radius)+(this->height*this->height))/(this->height*this->height);
  Matrix<double,3,1> w = Matrix<double,3,1>(wv);
  Matrix<double,3,3> dc_dct = dc*dc.transpose();
  Matrix<double,3,3> M = Matrix<double,3,3>::identity() - ((dc_dct)*beta);
  a = (dr.transpose()*M*dr).getVal(0,0);
  b = -2*((dr.transpose()*M*w).getVal(0,0));
  c = (w.transpose()*M*w).getVal(0,0);
  delta = (b*b) - (4*a*c);
  if(delta<0){
    return closest_t;
  }

  t1 = (-b + std::sqrt(delta)) / (2*a);
  t2 = (-b - std::sqrt(delta)) / (2*a);

  tBase = this->baseLid.IntersectRay(O,D,tMin,tMax);
  if(tBase < closest_t){
    closest_t = tBase;
    this->intersectSurf = BOT;
  }

  Coordinate surfp1  =(D*t1 +O);
  Coordinate surfp2 = (D*t2 +O);

  Vector vectorPi1V = Vector(this->vertex - surfp1);
  Vector vectorPi2V = Vector(this->vertex - surfp2);

  double surfProjectionLength1 = Vector::dot(vectorPi1V,D);
  double surfProjectionLength2 = Vector::dot(vectorPi2V,D);
  if(surfProjectionLength1 > 0 && surfProjectionLength1<=this->height){
    if(t1<closest_t){
      closest_t = t1;
      this->intersectSurf = SURF;
    }
  }

  if(surfProjectionLength2 > 0 && surfProjectionLength2<=this->height){
    if(t2<closest_t){
      closest_t = t2;
      this->intersectSurf = SURF;
    }
  }

  return closest_t;







}