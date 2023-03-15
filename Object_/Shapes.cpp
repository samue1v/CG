
#include "Shapes.h"
#include <iostream>
#include "../DataStructures/DataConsts.h"
#include <stdio.h>

Shape3D::Shape3D() {}

Sphere::Sphere(Coordinate center, float radius, Material *material){
  this->center = center;
  this->radius = radius;
  this->material = (material);
  this->texture = nullptr;
  this->name = "undefined";
}

Sphere::Sphere(Coordinate center, float radius, Material *material,std::string name){
  this->center = center;
  this->radius = radius;
  this->material = (material);
  this->texture = nullptr;
  this->name = name;
}

std::string Sphere::getName(){
    return this->name;
}

Texture * Sphere::getTexture(){
  if(this->texture){
    return this->texture;
  }
  return nullptr;
}

Color Sphere::getTexel(Coordinate P,Coordinate O,Matrix<float,4,4> cameraToWorld){
  if(!this->texture){
    return Color();
  }
  Matrix<float,4,1> Pmatrix = Matrix<float,4,1>(P);
  Coordinate newCenter = (cameraToWorld*Matrix<float,4,1>(this->center)).toCoordinate();
  P = ((cameraToWorld)*Pmatrix).toCoordinate();
 
  float x = (P.x -newCenter.x);
  float y = (P.y - newCenter.y);
  float z = (P.z - newCenter.z);

  //float v = (atan(sqrtf(x*x + y*y)/z) + PI/2.0)/PI;

  //float v =  (acos(y/radius))/PI;
  float v =  (acos(y/radius))/PI;
  float u = (atan2(z,x)/(PI)+ 1);


  //float u = asin(x/sqrtf(x*x + z*z))/(2*PI);


  //std::cout<< "u: "<< u <<" v: " << v << "\n"; 
  Pair<int,int> wh = this->texture->getWH();

  Color c = this->texture->getColorAt( abs((int)(floor(u * wh.left) )),abs((int)floor( v* wh.right)));
  return c;
}

void Sphere::transformView(Matrix<float,4,4> transformMatrix){
  Matrix<float,4,1> centerMatrix = Matrix<float,4,1>(this->center);
  this->center = (transformMatrix*centerMatrix).toCoordinate();
}

bool Sphere::setCenter(Coordinate newCenter) {
  this->center = newCenter;
  return true;
}

Coordinate Sphere::getCenter() { return this->center; }

bool Sphere::setRadius(float newRadius) {
  if (newRadius > 0) {
    this->radius = newRadius;
    return true;
  }
  return false;
}

float Sphere::getRadius() { return this->radius; }

bool Sphere::setMaterial(Material *material) {
  this->material = material;
  return true;
}

bool Sphere::setTexture(const std::string & filePath,SDL_Renderer * renderer){
  this->texture = new Texture(filePath,renderer);
  return true;
}


float Sphere::IntersectRay(Coordinate O, Vector3D D,float tMin,float tMax) {
  float r = this->getRadius();
  Vector3D c_minus_o = Vector3D((O - this->getCenter()));
  float a = Vector3D::dot(D, D);
  float b = 2 * Vector3D::dot(c_minus_o, D);
  float c = Vector3D::dot(c_minus_o, c_minus_o) - r * r;

  float discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return INF;
  }

  float t1 = (-b + sqrt(discriminant)) / (2 * a);
  float t2 = (-b - sqrt(discriminant)) / (2 * a);

  if(t1>=tMin && t1<=tMax && t1<t2){
    return t1;
  }
  return t2;
}

Material *Sphere::getMaterial() { return (this->material); }

Vector3D Sphere::computeNormal(Coordinate P,Vector3D D) {
  return Vector3D(P - (this->center));
}

bool Sphere::setTransform(Transformation * t){
  if(dynamic_cast<Translate *>(t)){
    Matrix<float,4,1> centerMatrix = Matrix<float,4,1>(this->center);
    Matrix<float,4,1> transformedCenter = t->getTransform() * centerMatrix;
    this->center = transformedCenter.toCoordinate();
    return true;
  }
  else if(dynamic_cast<Scale *>(t)){
    float scaleFactor = t->getTransform().getVal(0,0);
    this->radius = radius * scaleFactor;
    return true;
  }
  
  else if(dynamic_cast<RotateXfixed*>(t) || dynamic_cast<RotateYfixed*>(t) || dynamic_cast<RotateZfixed*>(t)){
    Translate * tr = new Translate(-t->getFixedPoint().x,-t->getFixedPoint().y,-t->getFixedPoint().z);
    Translate * ntr = new Translate(t->getFixedPoint().x,t->getFixedPoint().y,t->getFixedPoint().z);
    this->setTransform(tr);
    this->center = (t->getTransform() * Matrix<float,4,1>(this->center)).toCoordinate();
    this->setTransform(ntr);
    return true;
  }
  return false;
  
}

Plane::Plane() {}

Plane::Plane(Coordinate planePoint, Vector3D normal, Material * material) {
  this->planePoint = planePoint;
  this->normal = normal;
  this->material = material;
  this->texture = nullptr;
  this->name = "undefined";
}

Plane::Plane(Coordinate planePoint, Vector3D normal, Material * material,std::string name) {
  this->planePoint = planePoint;
  this->normal = normal;
  this->material = material;
  this->texture = nullptr;
  this->name = name;
}

std::string Plane::getName(){
    return this->name;
}

Material *Plane::getMaterial() { return this->material; }

Vector3D Plane::computeNormal(Coordinate P,Vector3D D){ return this->normal;}

Texture * Plane::getTexture(){
  if(this->texture){
    return this->texture;
  }
  return nullptr;
} 

bool Plane::setplanePoint(Coordinate newPoint){
  this->planePoint = newPoint;
  return true;
}

Coordinate Plane::getplanePoint(){
  return this->planePoint;
}

void Plane::transformView(Matrix<float,4,4> transformMatrix){
  this->planePoint = (transformMatrix*Matrix<float,4,1>(this->planePoint)).toCoordinate();
  this->normal = (transformMatrix*Matrix<float,4,1>(this->normal)).toVector3D();
}

Color Plane::getTexel(Coordinate P,Coordinate O,Matrix<float,4,4> cameraToWorld){
  if(!this->texture){
    return Color();
  }
  float u,v;
  Coordinate planePointWorld = (cameraToWorld*Matrix<float,4,4>(planePoint)).toCoordinate();
  Coordinate PWorld = (cameraToWorld*Matrix<float,4,4>(P)).toCoordinate();
  Vector3D Pvec = Vector3D(PWorld-planePointWorld);
  Vector3D e1 = Vector3D::cross(this->normal,Vector3D(1,0,0));
  Vector3D e12 = Vector3D::cross(this->normal,Vector3D(0,0,1));
  if(e12.getLength()>e1.getLength()){
    e1 =e12;
  }
  e1.normalize();
  Vector3D e2 = Vector3D::cross(this->normal,e1);
  e2.normalize();

  v = (Vector3D::dot(e1,Pvec));
  u = (Vector3D::dot(e2,Pvec));

  Pair<int,int> wh = this->texture->getWH();

  //Color c = this->texture->getColorAt( (wh.left - ((int)abs(u)) % wh.left) - 1,wh.right  - (((int)abs(v))% wh.right)-1);
  
  //Quadrant checking
  Color c;
  int um,vm;
  int w,h;
  w = wh.left;//-1;
  h = wh.right;//-1;
  /*
  if(u<0 && v > 0){
    //std::cout<<"1\n";
    um = (w - ((int)floor(-u)) % w);
    vm = (int)floor(v)%h;
    //c = this->texture->getColorAt(um,vm);
    //std::cout<<"a"<<"\n";

     
  }
  else if(v<0 && u >0){
    //std::cout<<"2\n";
    //std::cout<<"b"<<"\n";
    //std::cout<< "u: " << ((int)floor(u))%wh.left <<"v: " <<(wh.right + ((int)floor(v))%-wh.right)<<"\n"; 
    um = (int)floor(u)%w;
    vm = h - (int)floor(-v)%h;
    //c = this->texture->getColorAt(um,vm);
    //exit(-1);
  }
  else if(v<0 && u < 0){
    //std::cout<<"3\n";
    //std::cout<< "u: " << -(wh.left + (((int)floor(u))%-wh.left)) <<"v: " <<(wh.right + ((int)floor(v))%-wh.right)<<"\n"; 
    um = w - ((int)floor(-u)%w);
    vm = (h - ((int)floor(-v))%h);
    //c = this->texture->getColorAt(um,vm);
    
    //std::cout<<"c"<<"\n";  
  }
  else{
    //std::cout<<"d"<<"\n";
    //std::cout<<"4\n";
    um = (int)floor(u)%w;
    vm = (int)floor(v)%h;
    
  
  }
  */
 um = (int)(abs(u))%w;
 vm = (int)(abs(v))%h;
  /*
  if(um==wh.left){
    um--;
  }
  else if(vm==wh.right){
    vm--;
  }
  */
  c = this->texture->getColorAt(um,vm);
  
  //Color c = this->texture->getColorAt( ((int)u % wh.left) - 1,((int)v % wh.right)-1);
  
  return c;
  
}

bool Plane::setTexture(const std::string & filePath,SDL_Renderer * renderer){
  this->texture = new Texture(filePath,renderer);
  return true;
}

Vector3D Plane::getNormal(){
  return this->normal;
}

bool Plane::setNormal(Vector3D newNormal){
  this->normal = newNormal;
  this->normal.normalize();
  return true;
}

float Plane::IntersectRay(Coordinate O, Vector3D D,float tMin,float tMax){
  Vector3D p_minuspi = Vector3D(this->planePoint - O);//mudei aqui
  float denom = Vector3D::dot(D,this->normal);
  
  if(abs(denom) < ZERO_PROX ){
    return INF;
  }
  float t = Vector3D::dot(p_minuspi,this->normal) / denom;
  if(t>=tMin && t<tMax){
  	return t;
  }
	return INF;
}

bool Plane::setTransform(Transformation * t){
  if(dynamic_cast<RotateX*>(t) || dynamic_cast<RotateY*>(t) || dynamic_cast<RotateZ*>(t)){
    Matrix<float,4,1> planeNormalm = Matrix<float,4,1>(this->normal);
    Matrix<float,4,1> planeNormalmTransformed = t->getTransform() * planeNormalm;
    this->normal = planeNormalmTransformed.toVector3D();
    return true;
  }
  else if(dynamic_cast<Translate*>(t)){
    Matrix<float,4,1> pointMatrix = Matrix<float,4,1>(this->planePoint);
    Matrix<float,4,1> transformedPoint = t->getTransform() * pointMatrix;
    this->planePoint = transformedPoint.toCoordinate();
    return true;
  }
  else if(dynamic_cast<RotateX *>(t) || dynamic_cast<RotateY *>(t) || dynamic_cast<RotateZ *>(t)){
    Matrix<float,4,1> planeNormalm = Matrix<float,4,1>(this->normal);
    Matrix<float,4,1> planeNormalmTransformed = t->getTransform() * planeNormalm;
    this->normal = planeNormalmTransformed.toVector3D();
    return true;
  }
  else if(dynamic_cast<RotateXfixed*>(t) || dynamic_cast<RotateYfixed*>(t) || dynamic_cast<RotateZfixed*>(t)){
    Matrix<float,4,1> planeNormalm = Matrix<float,4,1>(this->normal);
    Matrix<float,4,1> planePointm = Matrix<float,4,1>(this->planePoint); 
    Matrix<float,4,1> planeNormalmTransformed = t->getTransform() * planeNormalm;
    this->planePoint = (t->getTransform()*planePointm).toCoordinate();
    this->normal = planeNormalmTransformed.toVector3D();
    return true;
  }
  return false;
}

Cylinder::Cylinder(){}

Cylinder::Cylinder(Coordinate baseCenter, Vector3D axis, float radius, float height,Material * material)
: baseCenter(baseCenter),  axis(axis), radius(radius), height(height){

  this->name = "undefined";
  this->material = material;
  this->topCenter = (axis*height) + baseCenter;
  this->baseLid = Plane(baseCenter,axis*-1,nullptr);
  this->topLid = Plane(topCenter,axis,nullptr);
  this->texture = nullptr;
}

Cylinder::Cylinder(Coordinate baseCenter, Vector3D axis, float radius, float height,Material * material,std::string name)
: baseCenter(baseCenter),  axis(axis), radius(radius), height(height){

  this->name = name;
  this->material = material;
  this->topCenter = (axis*height) + baseCenter;
  this->baseLid = Plane(baseCenter,axis*-1,nullptr);
  this->topLid = Plane(topCenter,axis,nullptr);
  this->texture = nullptr;
}

std::string Cylinder::getName(){
    return this->name;
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

Color Cylinder::getTexel(Coordinate P,Coordinate O,Matrix<float,4,4> cameraToWorld){
  if(!this->texture){
    return Color();
  }
  float x = (P.x -baseCenter.x);
  float y = (P.y - baseCenter.y);
  float z = (P.z - baseCenter.z);
  
  //float v = (atan(sqrtf(x*x + y*y)/z) + PI/2.0)/PI;
  float v = P.y - baseCenter.y;
  float u = (atan2(x,z)/(2*PI)+ 0.5);
  //float u = asin(x/sqrtf(x*x + z*z))/(2*PI);


  std::cout<< "u: "<< u <<" v: " << v << "\n"; 
  Pair<int,int> wh = this->texture->getWH();

  Color c = this->texture->getColorAt( abs((int)(floor(u * wh.left) )),abs((int)floor( v* wh.right)));
  return c;
}

void Cylinder::transformView(Matrix<float,4,4> transformMatrix){
  this->axis = (transformMatrix * Matrix<float,4,1>(this->axis)).toVector3D();
  this->baseCenter = (transformMatrix * Matrix<float,4,1>(this->baseCenter)).toCoordinate();
  this->topCenter = (transformMatrix * Matrix<float,4,1>(this->topCenter)).toCoordinate();
  this->baseLid.transformView(transformMatrix);
  this->topLid.transformView(transformMatrix);
  
}

Vector3D Cylinder::computeNormal(Coordinate P,Vector3D D){


  if(this->intersectSurf == BOT){
    return this->baseLid.computeNormal(P,D);
  }
  else if(this->intersectSurf == TOP){
    return this->topLid.computeNormal(P,D);
  }


  /*
  Vector3D n = (*(this->M) * Matrix<float>(P - this->baseCenter))->toVector();
  n.normalize();
  */
  Vector3D V = Vector3D(P - this->baseCenter);
  float lv = V.getLength();
  float pll = sqrtf(lv*lv - (this->radius*this->radius));
  Coordinate Pl = ((this->axis) * pll) + this->baseCenter;
  Vector3D N = Vector3D(P-Pl);
  N.normalize();

  return N;
}

bool Cylinder::setTexture(const std::string & filePath,SDL_Renderer * renderer){
  this->texture = new Texture(filePath,renderer);
  return true;
}

float Cylinder::IntersectRay(Coordinate O, Vector3D D, float tMin, float tMax){
  float a,b,c;
  float delta;
  float closest_t = INF;
  float t1, t2;
  float tBase;
  float tTop;
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
    float baseTest = Vector3D(pi - this->baseCenter).getLength();
    if(baseTest > 0 && baseTest < this->radius){
      closest_t = tBase;
      intersectSurf = BOT;
    }
  }

  if(tTop >1 && tTop<INF){
    pi = (D * tTop) + O;
    float topTest = Vector3D(pi - this->topCenter).getLength();
    if(topTest > 0 && topTest < this->radius){
      if(closest_t > tTop){
        closest_t = tTop;
        intersectSurf = TOP;
      }
    }
  }

  Vector3D piSurf1 = Vector3D((D*t1 +O) - this->baseCenter);
  Vector3D piSurf2 = Vector3D((D*t2 +O) - this->baseCenter);

  float surfT1 = Vector3D::dot(piSurf1,this->axis);
  float surfT2 = Vector3D::dot(piSurf2,this->axis);
  float surfClosest_t;
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

bool Cylinder::setTransform(Transformation * t){
  if(dynamic_cast<Scale *>(t)){
    float scaleFactor = t->getTransform().getVal(0,0);
    this->height = scaleFactor * height;
    this->radius = scaleFactor * radius;
    this->topCenter = this->topCenter*scaleFactor;
    this->baseCenter = this->baseCenter*scaleFactor;
    this->topLid.setplanePoint(topCenter);
    this->baseLid.setplanePoint(baseCenter);
    return true;
  }
  else if(dynamic_cast<Translate *>(t)){
    Matrix<float,4,1> baseCenterMatrix = Matrix<float,4,1>(this->baseCenter);
    Matrix<float,4,1> topCenterMatrix = Matrix<float,4,1>(this->topCenter);
    Matrix<float,4,1> transformedBaseCenter = t->getTransform() * baseCenterMatrix;
    Matrix<float,4,1> transformedTopCenter = t->getTransform() * topCenterMatrix;
    this->baseCenter = transformedBaseCenter.toCoordinate();
    this->topCenter = transformedTopCenter.toCoordinate();
       
    this->baseLid.setTransform(t);
    this->topLid.setTransform(t);
    
    return true;
  }
  else if(dynamic_cast<RotateX*>(t) || dynamic_cast<RotateY*>(t) || dynamic_cast<RotateZ*>(t)){
    Matrix<float,4,1> axisM = Matrix<float,4,1>(this->axis);
    Matrix<float,4,1> axisTransformed = t->getTransform() * axisM;
    this->axis = axisTransformed.toVector3D(); 
    this->baseLid.setTransform(t);
    this->topCenter =(this->axis*this->height)+this->baseCenter;
    this->topLid.setplanePoint(topCenter);
    //olhar dps
    this->topLid.setTransform(t);
    
    return true;
  }
  else if(dynamic_cast<RotateXfixed*>(t) || dynamic_cast<RotateYfixed*>(t) || dynamic_cast<RotateZfixed*>(t)){
    Translate * tr = new Translate(-t->getFixedPoint().x,-t->getFixedPoint().y,-t->getFixedPoint().z);
    Translate * ntr = new Translate(t->getFixedPoint().x,t->getFixedPoint().y,t->getFixedPoint().z);
    this->setTransform(tr);
    Matrix<float,4,1> axisM = Matrix<float,4,1>(this->axis);
    Matrix<float,4,1> baseMatrix = Matrix<float,4,1>(this->baseCenter);//
    Matrix<float,4,1> topMatrix = Matrix<float,4,1>(this->topCenter);
    Matrix<float,4,1> axisTransformed = t->getTransform() * axisM;
    this->axis = axisTransformed.toVector3D(); 
    this->baseCenter = (t->getTransform()*baseMatrix).toCoordinate();//
    this->topCenter = (t->getTransform()*topMatrix).toCoordinate();
    this->baseLid.setTransform(t);
    this->topLid.setTransform(t);
    this->setTransform(ntr);

    return true;
  }
  
  return false;
  }


Cone::Cone(){}

Cone::Cone(Coordinate baseCenter,Vector3D axis,float radius,float height,Material * material) : baseCenter(baseCenter),axis(axis),radius(radius),height(height){
  this->name = "undefined";
  this->material = material;
  this->cosTeta = this->height /(std::sqrt(radius*radius + height*height));
  this->vertex = (axis*height)+baseCenter;
  this->baseLid = Plane(baseCenter,axis*-1,material);
  this->texture = nullptr;

}

Cone::Cone(Coordinate baseCenter,Vector3D axis,float radius,float height,Material * material,std::string name) : baseCenter(baseCenter),axis(axis),radius(radius),height(height){
  this->name = name;
  this->material = material;
  this->cosTeta = this->height /(std::sqrt(radius*radius + height*height));
  this->vertex = (axis*height)+baseCenter;
  this->baseLid = Plane(baseCenter,axis*-1,material);
  this->texture = nullptr;

}

std::string Cone::getName(){
    return this->name;
}

Texture * Cone::getTexture(){
  if(this->texture){
    return this->texture;
  }
  return nullptr;
}

Color Cone::getTexel(Coordinate P,Coordinate O,Matrix<float,4,4> cameraToWorld){
  if(!this->texture){
    return Color();
  }
  return Color();
}

Material * Cone::getMaterial(){
  return this->material;
}

void Cone::transformView(Matrix<float,4,4> transformMatrix){
  
  this->axis = (transformMatrix * Matrix<float,4,1>(this->axis)).toVector3D();
  this->baseCenter = (transformMatrix * Matrix<float,4,1>(this->baseCenter)).toCoordinate();
  this->vertex = (transformMatrix * Matrix<float,4,1>(this->vertex)).toCoordinate();
  this->baseLid.transformView(transformMatrix);

  
}

Vector3D Cone::computeNormal(Coordinate P,Vector3D D){
  if(this->intersectSurf == BOT){
    return this->axis*-1;
  }
  /*
  Vector3D pv = Vector3D(this->vertex - P);
  float xvLength = pv.getLength()/this->cosTeta; 
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

float Cone::IntersectRay(Coordinate O, Vector3D D, float tMin, float tMax){
  float a, b, c, t1, t2;
  float delta;
  float beta;
  float tBase;
  float closest_t = INF;
  Vector3D wv = Vector3D(this->vertex);
  
  Matrix<float,3,1> dr = Matrix<float,3,1>(D);
  Matrix<float,3,1> dc = Matrix<float,3,1>(this->axis);
  Matrix<float,1,3> dct = dc.transpose();
  beta = ((this->radius*this->radius)+(this->height*this->height))/(this->height*this->height);
  Matrix<float,3,1> w = Matrix<float,3,1>(wv);
  Matrix<float,3,3> dc_dct = dc*dct;
  Matrix<float,3,3> M = Matrix<float,3,3>::identity() - ((dc_dct)*beta);
  a = (dr.transpose()*M*dr).getVal(0,0);
  b = -2*((dr.transpose()*M*w).getVal(0,0));
  c = (w.transpose()*M*w).getVal(0,0);
  //std::cout<<"auqi\n";
  /*
  float drDotdc = Vector3D::dot(D,this->axis);
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
    float baseTest = Vector3D(pi - this->baseCenter).getLength();
    if(baseTest > 0 && baseTest<=this->radius){
      closest_t = tBase;
      this->intersectSurf = BOT;
    }
  }

  Coordinate surfp1  =(D*t1 +O);
  Coordinate surfp2 = (D*t2 +O);

  Vector3D vectorPi1V = Vector3D(this->vertex - surfp1);
  Vector3D vectorPi2V = Vector3D(this->vertex - surfp2);

  float surfProjectionLength1 = Vector3D::dot(vectorPi1V,this->axis);
  float surfProjectionLength2 = Vector3D::dot(vectorPi2V,this->axis);
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

bool Cone::setTransform(Transformation * t){
  if(dynamic_cast<Scale *>(t)){
    float scaleFactor = t->getTransform().getVal(0,0);
    this->height = scaleFactor * height;
    this->radius = scaleFactor * radius;
    this->vertex =  this->axis*this->height + this->baseCenter;
    return true;
  }
  else if(dynamic_cast<Translate *>(t)){
    Matrix<float,4,1> baseCenterMatrix = Matrix<float,4,1>(this->baseCenter);
    Matrix<float,4,1> vertexMatrix = Matrix<float,4,1>(this->vertex);
    Matrix<float,4,1> transformedBaseCenter = t->getTransform() * baseCenterMatrix;
    this->baseCenter = transformedBaseCenter.toCoordinate();
       
    this->baseLid.setTransform(t);
    this->vertex = (t->getTransform()*vertexMatrix).toCoordinate();
    return true;
  }
  else if(dynamic_cast<RotateX*>(t) || dynamic_cast<RotateY*>(t) || dynamic_cast<RotateZ*>(t)){
    Matrix<float,4,1> axisM = Matrix<float,4,1>(this->axis);
    //Matrix<float,4,1> vertexMatrix = Matrix<float,4,1>(this->vertex);//
    //Matrix<float,4,1> baseMatrix = Matrix<float,4,1>(this->baseCenter);//
    Matrix<float,4,1> axisTransformed = t->getTransform() * axisM;
    this->axis = axisTransformed.toVector3D(); 
    this->vertex = this->axis*this->height + this->baseCenter;
    //this->baseCenter = (t->getTransform()*baseMatrix).toCoordinate();//
    //this->vertex = (t->getTransform()*vertexMatrix).toCoordinate();//
    
    this->baseLid.setTransform(t);
    return true;
  }
  else if(dynamic_cast<RotateXfixed*>(t) || dynamic_cast<RotateYfixed*>(t) || dynamic_cast<RotateZfixed*>(t)){
    Translate * tr = new Translate(-t->getFixedPoint().x,-t->getFixedPoint().y,-t->getFixedPoint().z);
    Translate * ntr = new Translate(t->getFixedPoint().x,t->getFixedPoint().y,t->getFixedPoint().z);
    this->setTransform(tr);

    Matrix<float,4,1> axisM = Matrix<float,4,1>(this->axis);
    Matrix<float,4,1> vertexMatrix = Matrix<float,4,1>(this->vertex);//
    Matrix<float,4,1> baseMatrix = Matrix<float,4,1>(this->baseCenter);//
    Matrix<float,4,1> axisTransformed = t->getTransform() * axisM;
    this->vertex = (t->getTransform()*vertexMatrix).toCoordinate();//
    this->axis = axisTransformed.toVector3D(); 
    this->baseCenter = (t->getTransform()*baseMatrix).toCoordinate();//
    this->baseLid.setTransform(t);

    this->setTransform(ntr);

    return true;
  }
  return false;
}