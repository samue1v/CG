
#include "Shapes.h"
#include <iostream>
#include "../DataStructures/DataConsts.h"
#include <stdio.h>

Shape3D::Shape3D() {}

Sphere::Sphere(Coordinate center, double radius, Material *material)
    : Shape3D() {
  this->center = center;
  this->radius = radius;
  this->material = (material);
  this->texture = nullptr;
}

Texture * Sphere::getTexture(){
  if(this->texture){
    return this->texture;
  }
  return nullptr;
}

Color Sphere::getTexel(Coordinate P,Coordinate O){
  return Color();
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

bool Sphere::setTexture(const std::string & filePath,SDL_Renderer * renderer){
  this->texture = new Texture(filePath,renderer);
  return true;
}


double Sphere::IntersectRay(Coordinate O, Vector3D D,double tMin,double tMax) {
  double r = this->getRadius();
  Vector3D c_minus_o = Vector3D((O - this->getCenter()));
  double a = Vector3D::dot(D, D);
  double b = 2 * Vector3D::dot(c_minus_o, D);
  double c = Vector3D::dot(c_minus_o, c_minus_o) - r * r;

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

Vector3D Sphere::computeNormal(Coordinate P,Vector3D D) {
  return Vector3D(P - (this->center));
}

Plane::Plane() {}

Plane::Plane(Coordinate planePoint, Vector3D normal, Material * material) {
  this->planePoint = planePoint;
  this->normal = normal;
  this->material = material;
  this->texture = nullptr;
}

Material *Plane::getMaterial() { return this->material; }

Vector3D Plane::computeNormal(Coordinate P,Vector3D D){ return this->normal;}

Texture * Plane::getTexture(){
  if(this->texture){
    return this->texture;
  }
  return nullptr;
} 

Color Plane::getTexel(Coordinate P,Coordinate O){
  double u,v;
  Vector3D Pvec = Vector3D(P-O);
  Vector3D e1 = Vector3D::cross(this->normal,Vector3D(1,0,0));
  /*
  e1.normalize();
  if(abs(e1.getElementAt(0))<=ZERO_PROX && abs(e1.getElementAt(1))<=ZERO_PROX && abs(e1.getElementAt(2))<=ZERO_PROX){
    e1 = Vector3D::cross(this->normal,Vector3D(0,0,1));
    e1.normalize();
  }
  */
 Vector3D e12 = Vector3D::cross(this->normal,Vector3D(0,0,1));
 if(e12.getLength()>e1.getLength()){
  e1 =e12;
  std::cout<<"erro\n";
 }
  e1.normalize();
  Vector3D e2 = Vector3D::cross(this->normal,e1);
  e2.normalize();
  Pvec.normalize();
  u = (Vector3D::dot(e1,Pvec));
  v = (Vector3D::dot(e2,Pvec));
  double ubias = (u+1.0)/2.0;
  double vbias = (v+1.0)/2.0;
  
  Pair<int,int> wh = this->texture->getWH();
  //std::cout<<"width: "<<wh.left<<"height: "<<wh.right<<"\n";
  //std::cout<<"u: "<<ubias*wh.left<<" v: "<<vbias*wh.right<<"\n";
  Color c = this->texture->getColorAt((int)((ubias*wh.left)),(int)((vbias*wh.right)));
  return c;
}

bool Plane::setTexture(const std::string & filePath,SDL_Renderer * renderer){
  this->texture = new Texture(filePath,renderer);
  return true;
}

double Plane::IntersectRay(Coordinate O, Vector3D D,double tMin,double tMax){
  Vector3D p_minuspi = Vector3D(this->planePoint - O);//mudei aqui
  double denom = Vector3D::dot(D,this->normal);
  
  if(abs(denom) < ZERO_PROX ){
    return INF;
  }
  double t = Vector3D::dot(p_minuspi,this->normal) / denom;
  if(t>=tMin && t<tMax){
  	return t;
  }
	return INF;
}

Cylinder::Cylinder(){}

Cylinder::Cylinder(Coordinate baseCenter, Vector3D axis, double radius, double height,Material * material)
: baseCenter(baseCenter),  axis(axis), radius(radius), height(height){

  this->material = material;
  this->topCenter = (axis*height) + baseCenter;
  this->baseLid = Plane(baseCenter,axis*-1,new Cooper());
  this->topLid = Plane(topCenter,axis,new Cooper());
  this->texture = nullptr;
}

Material * Cylinder::getMaterial(){
  return this->material;
}

Texture * Cylinder::getTexture(){
  if(this->texture){
    return this->texture;
  }
  return nullptr;
}

Color Cylinder::getTexel(Coordinate P,Coordinate O){
  return Color();
}

Vector3D Cylinder::computeNormal(Coordinate P,Vector3D D){


  if(this->intersectSurf == BOT){
    return this->baseLid.computeNormal(P,D);
  }
  else if(this->intersectSurf == TOP){
    return this->topLid.computeNormal(P,D);
  }


  /*
  Vector3D n = (*(this->M) * Matrix<double>(P - this->baseCenter))->toVector();
  n.normalize();
  */
  Vector3D V = Vector3D(P - this->baseCenter);
  double lv = V.getLength();
  double pll = sqrt(lv*lv - (this->radius*this->radius));
  Coordinate Pl = ((this->axis) * pll) + this->baseCenter;
  Vector3D N = Vector3D(P-Pl);
  N.normalize();

  return N;
}

bool Cylinder::setTexture(const std::string & filePath,SDL_Renderer * renderer){
  this->texture = new Texture(filePath,renderer);
  return true;
}

double Cylinder::IntersectRay(Coordinate O, Vector3D D, double tMin, double tMax){
  double a,b,c;
  double delta;
  double closest_t = INF;
  double t1, t2;
  double tBase;
  double tTop;
  Vector3D w = Vector3D(O-this->baseCenter);
  a = 1-(Vector3D::dot(D,this->axis)*Vector3D::dot(D,this->axis));
  b = 2*(Vector3D::dot(w,D) - (Vector3D::dot(w,this->axis) * Vector3D::dot(D,this->axis)));
  c = Vector3D::dot(w,w) - (Vector3D::dot(w,this->axis)*Vector3D::dot(w,this->axis)) - (this->radius * this->radius);
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
    double baseTest = Vector3D(pi - this->baseCenter).getLength();
    if(baseTest > 0 && baseTest < this->radius){
      closest_t = tBase;
      intersectSurf = BOT;
    }
  }

  if(tTop >1 && tTop<INF){
    pi = (D * tTop) + O;
    double topTest = Vector3D(pi - this->topCenter).getLength();
    if(topTest > 0 && topTest < this->radius){
      if(closest_t > tTop){
        closest_t = tTop;
        intersectSurf = TOP;
      }
    }
  }

  Vector3D piSurf1 = Vector3D((D*t1 +O) - this->baseCenter);
  Vector3D piSurf2 = Vector3D((D*t2 +O) - this->baseCenter);

  double surfT1 = Vector3D::dot(piSurf1,this->axis);
  double surfT2 = Vector3D::dot(piSurf2,this->axis);
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

Cone::Cone(Coordinate baseCenter,Vector3D axis,double radius,double height,Material * material) : baseCenter(baseCenter),axis(axis),radius(radius),height(height){
  this->material = material;
  this->cosTeta = this->height /(std::sqrt(radius*radius + height*height));
  this->vertex = (axis*height)+baseCenter;
  this->baseLid = Plane(baseCenter,axis*-1,material);
  this->texture = nullptr;

}

Texture * Cone::getTexture(){
  if(this->texture){
    return this->texture;
  }
  return nullptr;
}

Color Cone::getTexel(Coordinate P,Coordinate O){
  return Color();
}

Material * Cone::getMaterial(){
  return this->material;
}

Vector3D Cone::computeNormal(Coordinate P,Vector3D D){
  if(this->intersectSurf == BOT){
    return this->axis*-1;
  }
  /*
  Vector3D pv = Vector3D(this->vertex - P);
  double xvLength = pv.getLength()/this->cosTeta; 
  Coordinate x = (this->axis*(this->height-xvLength)) + this->baseCenter;
  Vector3D n = Vector3D(P - x);
  n.normalize();
  */
  /*
  Vector3D vp = Vector3D(this->vertex - P);
  Vector3D nbar = Vector3D::cross(vp,this->axis);
  Vector3D n = Vector3D::cross(nbar,vp);
  n.normalize();  */
  Vector3D v_pi = Vector3D(this->vertex - P);
  v_pi.normalize();
  Vector3D nbar = Vector3D::cross(v_pi,this->axis);
  Vector3D n = Vector3D::cross(nbar,v_pi);
  n.normalize();
  return n;
}


bool Cone::setTexture(const std::string & filePath,SDL_Renderer * renderer){
  this->texture = new Texture(filePath,renderer);
  return true;
}

double Cone::IntersectRay(Coordinate O, Vector3D D, double tMin, double tMax){
  double a, b, c, t1, t2;
  double delta;
  double beta;
  double tBase;
  double closest_t = INF;
  Vector3D wv = Vector3D(this->vertex - O);
  
  Matrix<double,3,1> dr = Matrix<double,3,1>(D);
  Matrix<double,3,1> dc = Matrix<double,3,1>(this->axis);
  Matrix<double,1,3> dct = dc.transpose();
  //t1 norm
  //wv.normalize();
  beta = ((this->radius*this->radius)+(this->height*this->height))/(this->height*this->height);
  Matrix<double,3,1> w = Matrix<double,3,1>(wv);
  Matrix<double,3,3> dc_dct = dc*dct;
  Matrix<double,3,3> M = Matrix<double,3,3>::identity() - ((dc_dct)*beta);
  //std::cout<< this->height <<'\n';
  //std::cout<< beta <<'\n';
  //std::cout<< M;
  //std::cout<< '\n';
  //exit(-1);
  a = (dr.transpose()*M*dr).getVal(0,0);
  b = -2*((dr.transpose()*M*w).getVal(0,0));
  c = (w.transpose()*M*w).getVal(0,0);
  
  /*
  double drDotdc = Vector3D::dot(D,this->axis);
  a = (drDotdc*drDotdc) - Vector3D::dot(D,D)*(this->cosTeta*this->cosTeta);
  b = 2*((Vector3D::dot(wv,D)*(cosTeta*cosTeta)) - (Vector3D::dot(wv,this->axis) * drDotdc));
  c = (Vector3D::dot(wv,this->axis)*Vector3D::dot(wv,this->axis)) - Vector3D::dot(wv,wv)*(this->cosTeta*this->cosTeta);
  */
  delta = (b*b) - (4*a*c);
  if(delta<0){
    return closest_t;
  }
  if(a!=0){
    t1 = (-b + std::sqrt(delta)) / (2*a);
    t2 = (-b - std::sqrt(delta)) / (2*a);
  }
  else{
    t1 = -c/b;
    t2 = t1;
  }

  tBase = this->baseLid.IntersectRay(O,D,tMin,tMax);
  
  if(tBase <INF && tBase>1){
    Coordinate pi = (D*tBase) + O;
    double baseTest = Vector3D(pi - this->baseCenter).getLength();
    if(baseTest > 0 && baseTest<=this->radius){
      closest_t = tBase;
      this->intersectSurf = BOT;
    }
  }

  Coordinate surfp1  =(D*t1 +O);
  Coordinate surfp2 = (D*t2 +O);

  Vector3D vectorPi1V = Vector3D(this->vertex - surfp1);
  Vector3D vectorPi2V = Vector3D(this->vertex - surfp2);

  double surfProjectionLength1 = Vector3D::dot(vectorPi1V,this->axis);
  double surfProjectionLength2 = Vector3D::dot(vectorPi2V,this->axis);
  if(surfProjectionLength1 > 0 && surfProjectionLength1<=this->height){
    if(t1>0 && t1<closest_t){
      closest_t = t1;
      this->intersectSurf = SURF;
    }
  }

  if(surfProjectionLength2 > 0 && surfProjectionLength2<=this->height){
    if(t2>0 && t2<closest_t){
      closest_t = t2;
      this->intersectSurf = SURF;
    }
  }

  return closest_t;

}