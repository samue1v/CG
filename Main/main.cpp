/*
LEMBRAR!!!! lembre do que ocorreu com a camera e a transformaçaõ em objeto.
*/

#include "../Canvas_/Canvas.h"
#include "../Camera/Camera.h"
#include "../DataStructures/Coordinate.h"
#include "../DataStructures/DataConsts.h"
#include "../DataStructures/Matrix.h"
#include "../DataStructures/Vector.h"
#include "../Ilumination/Color.h"
#include "../Ilumination/Intensity.h"
#include "../Ilumination/Light.h"
#include "../Ilumination/Reflect.h"
#include "../Object_/Object.h"
#include "../Object_/Shapes.h"
#include "../Object_/Transformation.h"
#include "../Object_/Texture.h"
#include "../World/Scene.h"
#include "../World/Space3D.h"
#include <unistd.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <future>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include "../libs/glfw/include/GLFW/glfw3.h"
#include <GLFW/glfw3.h>

const int nLines = 600;
const int nColumns = 600;

Canvas<nLines,nColumns> * canvas;
Scene * scene;
GLFWwindow* window;
GLuint tex_handle;

void setGlfw();
void display();
void constructScene();
double run();
bool menuObj(Object *);
void menuMain();
bool shapeListMenu(Shape3D *);
bool menuShape(Object *);
bool menuTransform(Object *);
bool menuTransform(Shape3D *);
bool menuTransform(Mesh *);
bool menuMaterial(Object *);
bool menuMaterial(Shape3D *);
bool menuMaterial(Mesh *);

bool writePPM() {
  std::ofstream myfile;
  //Matrix<Color,l,k> *m = canvas->getCanvas();
  myfile.open("image.ppm");
  myfile << "P3\n";
  myfile << canvas->getNumberLines() << ' ' << canvas->getNumberColumns()
         << '\n';
  myfile << 255 << '\n';
  unsigned char RGBarray[6];
  RGBarray[1] = ' ';
  RGBarray[3] = ' ';
  RGBarray[5] = ' ';
  for (int i = 0; i < canvas->getNumberLines(); i++) {
    for (int j = 0; j < canvas->getNumberColumns(); j++) {
      Color c = canvas->getColorAt(i,j);
      //std::cout<<(c);
      myfile << ' ' << (int)c.red << ' '
             << (int)c.green << ' ' << (int)c.blue
             << ' ';
    }
    myfile << '\n';
  }
  return true;
}

template<int l,int k>
bool SDLdraw(Canvas<l,k> *canvas){
  Matrix<Color,l,k> *m = canvas->getCanvas();
  SDL_Window * window =nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(500,500, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);
  for(int i =0;i<l;i++){
    for(int j = 0;j>k;j++){
        SDL_SetRenderDrawColor(renderer,(int)m->getVal(i, j).red,(int)m->getVal(i, j).green,(int)m->getVal(i, j).blue,255);
        SDL_RenderDrawPoint(renderer,i,j);

    }
  }
  SDL_RenderPresent(renderer);
  SDL_Delay(10000);
  return true;
}

void constructScene(){
  SDL_Renderer * renderer = nullptr;
  double sphereDistance = 60;

  Coordinate eye = Coordinate(0,0,10);
  Coordinate up = Coordinate(0,2000,20);
  Coordinate lookAt = Coordinate(0,0,-100);  

  Camera * camera  = new Camera(eye,lookAt,up);

  // inicialização da cena e da esfera
  double radius = 100;

  Coordinate center = Coordinate(0, 0, -(sphereDistance + radius));

  

  //Materials
  Rubber *rubber = new Rubber();
  Metal *metal = new Metal();
  Plastic *plastic = new Plastic();
  Cooper *cooper = new Cooper();
  Marble *marble = new Marble();

  Object * lamp = new Object("lampada");
  Cylinder * lampBase = new Cylinder(Coordinate(0,0,0),Vector3D(0,1,0),0.5,0.3,marble,"base lampada.");
  Sphere * lampBulb = new Sphere(Coordinate(0,-0.1,0),0.25,marble,"bulbo lampada");

  lamp->setShape(lampBase);
  lamp->setShape(lampBulb);
  lamp->setTransform(new Translate(0,2,5));

  Object * house = new Object("house");
  Mesh * house_mesh = new Mesh("../MeshFiles/casa.obj",marble,"house_mesh");
  house_mesh->setTransform(new Scale(0.2,0.2,0.2));
  house_mesh->setTexture("../TextureFiles/wood.png",renderer);
  house->setMesh(house_mesh);

  //Sphere
  Sphere *circle = new Sphere(Coordinate(0,0,-10), 1, rubber,"esfera teste");
  //circle->setTransform(new Scale(0.5,1,1));
  //circle->setTransform(new Translate(50,10,-100));
  

  //Cylinder
  Vector3D cylinderAxis = Vector3D(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
  Cylinder * cylinder = new Cylinder(Coordinate(10,0,-100),Vector3D(1,0,0),20,50,marble,"cilindro teste");
  Coordinate cylinderTop = (cylinderAxis*3*radius)+center;

  //cylinder->setTransform(new RotateX(120));
  //cylinder->setTransform(new Translate(120,90,-60));
  //cylinder->setTransform(new Scale(2,3,3));
  
  
  //Cone
  double coneRadius = 1.5*radius;
  //Cone * cone = new Cone(cylinderTop,cylinderAxis,coneRadius,coneRadius/3,marble);
  Cone * coneup = new Cone(Coordinate(0,10,-100),Vector3D(0,1,0),10,20,marble,"coneup estrela");
  Cone * conedown = new Cone(Coordinate(0,-10,-100),Vector3D(0,-1,0),10,20,rubber,"conedown estrela");
  Cone * coneleft = new Cone(Coordinate(-10,0,-100),Vector3D(-1,0,0),10,20,marble,"coneleft estrela");
  Cone * coneright = new Cone(Coordinate(10,0,-100),Vector3D(1,0,0),10,20,marble,"coneright estrela");
  //Cone * cone = new Cone(Coordinate(0,0,-100),Vector3D(-1,0,0),radius,radius*2,marble);
  //cone->setTransform(new Translate(-50,100,10));
  //cone->setTransform(new RotateX(-45));
  //cone->setTransform(new RotateY(45));


  //Planes
	Coordinate floorPoint = Coordinate(0,-20,0);
	Vector3D floorNormal = Vector3D(0,1,0);
  Coordinate backPoint = Coordinate(0,0,-400);
	Vector3D backNormal = Vector3D(0,0,-1);
	Plane *floorPlane = new Plane(floorPoint, floorNormal, rubber);
	Plane *backPlane = new Plane(backPoint, backNormal, metal);

  //floorPlane->setTransform(new RotateX(30));


  //textures
  floorPlane->setTexture("../TextureFiles/wood.png",renderer);
  circle->setTexture("../TextureFiles/teste.png",renderer);
  backPlane->setTexture("../TextureFiles/floor.png",renderer);

  //Meshes
  std::string simple_mesh = "../MeshFiles/unitcube.obj";
  std::string moldura_mesh = "../MeshFiles/moldura.obj";
  std::string casa_mesh = "../MeshFiles/casa.obj";
  std::string quadro_mesh = "../MeshFiles/frame.obj";
  Mesh * moldura = new Mesh(moldura_mesh,marble);
  moldura->setTexture("../TextureFiles/wood_moldura.png",renderer);
  Mesh * pintura = new Mesh(quadro_mesh,marble);
  pintura->setTexture("../TextureFiles/kaguya.png",renderer);
  
  //rightwood->setTransform(new Scale(10,10,10));
  //rightwood->setTransform(new Translate(0,0,-100));
  
  //bottomwood->setTransform(new Scale(0.2,0.1,0.1));
  //topwood->setTransform(new Scale(0.6,0.1,0.1));
  //topwood->setTransform(new Translate(0,20,0));
  //leftwood->setTransform(new Scale(0.6,0.1,0.1));

  //rightwood->setTransform(new RotateZfixed(-180,Coordinate(-1,1,0)));
  //leftwood->setTransform(new RotateZfixed(180,Coordinate(1,1,0)));
  //topwood->setTransform(new Translate(0,4,0));
  moldura->setTransform(new RotateZ(90));
  moldura->setTransform(new RotateX(90));
  pintura->setTransform(new RotateX(90));
  pintura->setTransform(new Scale(4,3,1));
  //pintura->setTransform(new RotateY(180));
  //pintura->setTransform(new Translate(0,0,2));
  

  //rightwood->setTransform(new Scale(0.2,0.1,0.1));
  //Mesh * mesh = new Mesh(casa_mesh,marble);
  //mesh->setTransform(new Translate(25,0,0));
  //mesh->setTransform(new Scale(0.8,0.8,0.8));
  
  //mesh->setTransform(new Scale(20,20,20));
  //mesh->setTransform(new RotateY(-135));
  //mesh->setTransform(new RotateX(-135));
  //mesh->setTransform(new RotateZ(30));
  //mesh->setTransform(new ShearYX(30));
  
  //mesh->setTexture("../TextureFiles/kaguya.png",renderer);
  
  //Object
  std::string name = "circulo";
  std::string plano = "plane";
  std::string quadronome = "quadro";

  Object * quadro = new Object(quadronome);
  //Object *obj = new Object(name);
  Object *objPlane = new Object(plano);

  //Setting shapes and meshes to object

  //obj->setShape(circle);
  //obj->setShape(floorPlane);
  //obj->setShape(backPlane);
  //obj->setMesh(mesh);
  //quadro->setMesh(bottomwood);
  //quadro->setMesh(topwood);
  //quadro->setMesh(leftwood);
  //quadro->setMesh(rightwood);
  quadro->setMesh(moldura);
  quadro->setMesh(pintura);
  quadro->setTransform(new Translate(2,2,0));
  quadro->setTransform(new RotateX(45));
  quadro->setTransform(new RotateX(30));
  
  quadro->setTransform(new RotateX(-75));
  //obj->setShape(cylinder);
  //obj->setShape(coneleft);  
  //obj->setShape(coneright);
  //obj->setShape(coneup);
  //obj->setShape(conedown);


  objPlane->setShape(floorPlane);
  //objPlane->setMesh(rightwood);
  
 // obj->setTransform(new RotateZ(45));
  //obj->setTransform(new Translate(0,0,50));
  //obj->setTransform(new Scale(20,20,20));
  
  //obj->setTransform(new RotateYfixed(180,Coordinate(0,0,-10)));
  //obj->setTransform(new RotateXfixed(30,Coordinate(0,0,-10)));
  //obj->setTransform(new RotateY(360));
  //obj->setTransform(new RotateZfixed(45,Coordinate(0,0,-100)));
  //obj->setTransform(new Translate(20,20,20));
  //obj->setTransform(new Scale(10,10,1));


  
  //Setting lights

  Intensity ambientIntensity = Intensity(0.2, 0.2, 0.2);
  AmbientLight *ambientLight = new AmbientLight(ambientIntensity,"Ambiente Light");
  Intensity pointIntensity = Intensity(0.7, 0.7, 0.7);
  PointLight *pointLight =new PointLight(pointIntensity, Coordinate(0,1.4,5),"PointLight");//Coordinate(0,60,-30))
  //PointLight *pointLight2 =new PointLight(pointIntensity, Coordinate(0,200 ,1000));
  PointLight *pointLight3 =new PointLight(pointIntensity, Coordinate(5,5,15),"PointLight3");
  DirectionalLight * dirLight = new DirectionalLight(Intensity(0.2,0.2,0.2),Vector3D(0,0,-1),"DirLIght");
  //Creating the scene
  
  scene->setObject(quadro);
  scene->setObject(objPlane);
  scene->setObject(lamp);
  //scene->setObject(house);


  scene->setLight(ambientLight);
  //scene->setLight(dirLight);
  scene->setLight(pointLight);
  //scene.setLight(pointLight2);
  scene->setLight(pointLight3);
  scene->setCamera(camera);
  scene->transformView();
  
}

double run(){
  Pair<double,double> windowSize = canvas->getWindowSize();
  double wj = windowSize.left;
  double hj = windowSize.right;
  Pair<double,double> gridSize = canvas->getGridSize();
  double dx = gridSize.left;
  double dy = gridSize.right;
  Coordinate P0 = scene->getCamera()->getEyeTransformed();
  for (int l = 0; l < nLines; l++) {
    double y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      double x = -wj / 2 + dx / 2 + c * dx;
      Coordinate canvasPoint = Coordinate(x, y, canvas->getCanvasDistance());
      Vector3D dr = Vector3D(canvasPoint - P0);
      dr.normalize();
      Triple<Object *,Intensity,Color> hitData = Space3D::TraceRay(scene, P0, dr, 1, INF); 
      canvas->setObjectAt(c,l,hitData.left);
      if(hitData.right.hasInit){
        canvas->pushColorBuffer(l,c,hitData.right * hitData.middle);
      }
      else{
        canvas->pushColorBuffer(l,c,scene->getNaturalColor() * hitData.middle);
      }
    }
  }
  return 1.0;
}

void ErrorCallback(int, const char* err_str)
{
    std::cout << "GLFW Error: " << err_str << std::endl;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    bool flag = false;
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
    {
      //clicked = true;
       //getting cursor position
       double xMousePos,yMousePos;
       glfwGetCursorPos(window, &xMousePos, &yMousePos);
       Object * obj = canvas->getObjectAtCoord(xMousePos,yMousePos);
       obj->applyViewTransform(scene->getCamera()->getCameraToWorld());
       flag = menuObj(obj);
       obj->applyViewTransform(scene->getCamera()->getWorldToCamera());
       if(flag){
        run();
        std::cout<<"Success.\n";
       }
       else{
        std::cout<<"Nothing done.\n";
       }
       //canvas->getObjectAtCoord(xMousePos,yMousePos)->setTransform(new RotateX(45));
       //run();
       
       //auto a = std::async(std::launch::async, menuObj,canvas->getObjectAtCoord(xMousePos,yMousePos));
       
       //std::cout<<"passei\n";
       //canvas->getObjectAtCoord(xMousePos,yMousePos)->setTransform(new RotateZ(-45));
        //std::async(std::launch::async,run); 

       //std::cout << "Cursor Position at (" << xMousePos << " : " << yMousePos <<")"<< "\n";
       
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) 
    {
      menuMain();
       
    }

}

bool menuChangeLight(Light * light){
  int option;
  bool flag = false;
  std::cout<<"Chose any option: \n";
  std::cout<<"(1)Flip Switch.\n";
  std::cout<<"(2)Change Location.\n";
  std::cout<<"(3)Change Intensity.\n";
  std::cout<<"(4)Exit.\n";
  std::cout<<"Option: \n";
  std::cin >> option;
  if(option == 1){
    light->flipSwitch();
    flag = true;
  }
  else if(option == 2){
    if(static_cast<DirectionalLight *>(light)){
      double x,y,z;
      DirectionalLight * dirlight = static_cast<DirectionalLight *>(light);
      std::cout<<"Digite o valor de x da direção: \n";
      std::cin>>x;
      std::cout<<"Digite o valor de y da direção: \n";
      std::cin>>y;
      std::cout<<"Digite o valor de Z da direção: \n";
      dirlight->setDirection(Vector3D(x,y,z));
      flag = true;
    }
    else if(static_cast<PointLight *>(light)){
      double x,y,z;
      PointLight * pointlight = static_cast<PointLight *>(light);
      std::cout<<"Digite o valor de x da coordenada: \n";
      std::cin>>x;
      std::cout<<"Digite o valor de y da coordenada: \n";
      std::cin>>y;
      std::cout<<"Digite o valor de Z da coordenada: \n";
      pointlight->setPosition(Coordinate(x,y,z));
      flag = true;
    }
    else if(static_cast<AmbientLight *>(light)){}
    //else if(spotlight)
  }
  else if(option == 3){
    double ir,ig,ib;
    std::cout<<"Digite o valor de ir: \n";
    std::cin>>ir;
    std::cout<<"Digite o valor de ig: \n";
    std::cin>>ig;
    std::cout<<"Digite o valor de ib: \n";
    std::cin>>ib;
    light->setIntensity(Intensity(ir,ig,ib));
    flag = true;
  }
  else{

  }
  return flag;

}

bool menuTransform(Shape3D * inp){
  int option;
  bool flag = false;
  std::cout<<"Chose any option: \n";
  std::cout<<"(1)Apply Translate.\n";
  std::cout<<"(2)Apply Scale.\n";
  std::cout<<"(3)Apply RotateX.\n";
  std::cout<<"(4)Apply RotateY.\n";
  std::cout<<"(5)Apply RotateZ.\n";
  std::cout<<"(6)Apply RotateFixedX.\n";
  std::cout<<"(7)Apply RotateFixedY.\n";
  std::cout<<"(8)Apply RotateFixedZ.\n";
  std::cout<<"(9)Apply ShearXY.\n";
  std::cout<<"(10)Apply ShearYX.\n";
  std::cout<<"(11)Apply ShearXZ.\n";
  std::cout<<"(12)Apply ShearZX.\n";
  std::cout<<"(13)Apply ShearYZ.\n";
  std::cout<<"(14)Apply ShearZY.\n";
  std::cout<<"(15)Exit";
  std::cout<<"Option: \n";
  std::cin >> option;
  std::cout<< "\n" << std::flush;

  if(option == 1){
    double x,y,z;
    std::cout<<"Digite o valor de x: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z: \n";
    std::cin>>y;
    std::cout<<"\n";
    inp->setTransform(new Translate(x,y,z));
    flag =  true;

  }
  else if(option == 2){
    double x,y,z;
    std::cout<<"Digite o valor de x: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z: \n";
    std::cin>>y;
    std::cout<<"\n";
    inp->setTransform(new Scale(x,y,z));
    flag =  true;
  }
  else if(option == 3){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateX(degree));
    flag =  true;


  }
  else if(option == 4){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateY(degree));
    flag = true;

  }
  else if(option == 5){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateZ(degree));
    flag = true;

  }
  else if(option == 6){
    double degree,x,y,z;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    std::cout<<"Digite o valor de x da coordenada: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y da coordenada: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z da coordenda: \n";
    inp->setTransform(new RotateXfixed(degree,Coordinate(x,y,z)));
    flag = true;
  }
  else if(option == 7){
    double degree,x,y,z;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    std::cout<<"Digite o valor de x da coordenada: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y da coordenada: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z da coordenda: \n";
    inp->setTransform(new RotateYfixed(degree,Coordinate(x,y,z)));
    flag = true;
  }
  else if(option == 8){
    double degree,x,y,z;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    std::cout<<"Digite o valor de x da coordenada: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y da coordenada: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z da coordenda: \n";
    inp->setTransform(new RotateZfixed(degree,Coordinate(x,y,z)));
    flag = true;
  }
  else if(option == 9){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 10){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 11){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 12){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 13){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 14){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else{
    flag = false;
  }


  return flag;
}

bool menuTransform(Object * inp){
  int option;
  bool flag = false;
  std::cout<<"Chose any option: \n";
  std::cout<<"(1)Apply Translate.\n";
  std::cout<<"(2)Apply Scale.\n";
  std::cout<<"(3)Apply RotateX.\n";
  std::cout<<"(4)Apply RotateY.\n";
  std::cout<<"(5)Apply RotateZ.\n";
  std::cout<<"(6)Apply RotateFixedX.\n";
  std::cout<<"(7)Apply RotateFixedY.\n";
  std::cout<<"(8)Apply RotateFixedZ.\n";
  std::cout<<"(9)Apply ShearXY.\n";
  std::cout<<"(10)Apply ShearYX.\n";
  std::cout<<"(11)Apply ShearXZ.\n";
  std::cout<<"(12)Apply ShearZX.\n";
  std::cout<<"(13)Apply ShearYZ.\n";
  std::cout<<"(14)Apply ShearZY.\n";
  std::cout<<"(15)Exit";
  std::cout<<"Option: \n";
  std::cin >> option;
  std::cout<< "\n" << std::flush;

  if(option == 1){
    double x,y,z;
    std::cout<<"Digite o valor de x: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z: \n";
    std::cin>>z;
    std::cout<<"\n";
    inp->setTransform(new Translate(x,y,z));
    flag = true;

  }
  else if(option == 2){
    double x,y,z;
    std::cout<<"Digite o valor de x: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z: \n";
    std::cin>>z;
    std::cout<<"\n";
    inp->setTransform(new Scale(x,y,z));
    flag = true;
  }
  else if(option == 3){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateX(degree));
    flag = true;


  }
  else if(option == 4){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateY(degree));
    flag = true;
  }
  else if(option == 5){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateZ(degree));
    flag = true;
  }
  else if(option == 6){
    double degree,x,y,z;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    std::cout<<"Digite o valor de x da coordenada: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y da coordenada: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z da coordenda: \n";
    std::cin>>z;
    inp->setTransform(new RotateXfixed(degree,Coordinate(x,y,z)));
    flag = true;
  }
  else if(option == 7){
    double degree,x,y,z;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    std::cout<<"Digite o valor de x da coordenada: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y da coordenada: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z da coordenda: \n";
    std::cin>>z;
    inp->setTransform(new RotateYfixed(degree,Coordinate(x,y,z)));
    flag = true;
  }
  else if(option == 8){
    double degree,x,y,z;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    std::cout<<"Digite o valor de x da coordenada: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y da coordenada: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z da coordenda: \n";
    std::cin>>z;
    inp->setTransform(new RotateZfixed(degree,Coordinate(x,y,z)));
    flag = true;
  }
  else if(option == 9){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 10){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 11){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 12){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 13){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else if(option == 14){
    std::cout<<"Operação não suportada.\n";
    flag = false;
  }
  else{
    std::cout<<"Invalid option.\n";
    flag = false;
  }
  //std::cout<<option<<"\n";
  return flag;
}

bool menuTransform(Mesh * inp){
  int option;
  bool flag = false;
  std::cout<<"Chose any option: \n";
  std::cout<<"(1)Apply Translate.\n";
  std::cout<<"(2)Apply Scale.\n";
  std::cout<<"(3)Apply RotateX.\n";
  std::cout<<"(4)Apply RotateY.\n";
  std::cout<<"(5)Apply RotateZ.\n";
  std::cout<<"(6)Apply RotateFixedX.\n";
  std::cout<<"(7)Apply RotateFixedY.\n";
  std::cout<<"(8)Apply RotateFixedZ.\n";
  std::cout<<"(9)Apply ShearXY.\n";
  std::cout<<"(10)Apply ShearYX.\n";
  std::cout<<"(11)Apply ShearXZ.\n";
  std::cout<<"(12)Apply ShearZX.\n";
  std::cout<<"(13)Apply ShearYZ.\n";
  std::cout<<"(14)Apply ShearZY.\n";
  std::cout<<"(15)Exit";
  std::cout<<"Option: \n";
  std::cin >> option;
  std::cout<< "\n" << std::flush;

  if(option == 1){
    double x,y,z;
    std::cout<<"Digite o valor de x: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z: \n";
    std::cin>>z;
    std::cout<<"\n";
    inp->setTransform(new Translate(x,y,z));
    flag = true;

  }
  else if(option == 2){
    double x,y,z;
    std::cout<<"Digite o valor de x: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z: \n";
    std::cin>>z;
    std::cout<<"\n";
    inp->setTransform(new Scale(x,y,z));
    flag = true;
  }
  else if(option == 3){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateX(degree));
    flag = true;

  }
  else if(option == 4){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateY(degree));
    flag = true;
  }
  else if(option == 5){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateZ(degree));

  }
  else if(option == 6){
    double degree,x,y,z;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    std::cout<<"Digite o valor de x da coordenada: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y da coordenada: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z da coordenda: \n";
    std::cin>>z;
    inp->setTransform(new RotateXfixed(degree,Coordinate(x,y,z)));
    flag = true;
  }
  else if(option == 7){
    double degree,x,y,z;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    std::cout<<"Digite o valor de x da coordenada: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y da coordenada: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z da coordenda: \n";
    std::cin>>z;
    inp->setTransform(new RotateYfixed(degree,Coordinate(x,y,z)));
    flag = true;
  }
  else if(option == 8){
    double degree,x,y,z;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    std::cout<<"Digite o valor de x da coordenada: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y da coordenada: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z da coordenda: \n";
    std::cin>>z;
    inp->setTransform(new RotateZfixed(degree,Coordinate(x,y,z)));
    flag = true;
  }
  else if(option == 9){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearXY(degree));
    flag = true;
  }
  else if(option == 10){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearYX(degree));
    flag = true;
  }
  else if(option == 11){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearXZ(degree));
    flag = true;
  }
  else if(option == 12){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearZX(degree));
    flag = true;
  }
  else if(option == 13){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearYZ(degree));
    flag = true;
  }
  else if(option == 14){
    double degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearZY(degree));
    flag = true;
  }
  else{
    flag = false;
  }
  
  return flag;
}

bool menuMaterial(Shape3D * shape){
  int option;
  bool flag = false;
  Material * material = shape->getMaterial();
  std::cout<<material;
  std::cout<<"(1)Change Ka\n";
  std::cout<<"(2)Change Kd\n";
  std::cout<<"(3)Change Ke\n";
  std::cout<<"(4)Exit\n";
  std::cin>>option;
  if(option == 1){
    double kr,kg,kb;
    std::cout<<"kr: \n";
    std::cin>>kr;
    std::cout<<"kg: \n";
    std::cin>>kg;
    std::cout<<"kb: \n";
    std::cin>>kb;
    material->setKa(AmbientReflectiveness(Coeficients(kr,kg,kb)));
    flag = true;

  }
  else if(option == 2){
    double kr,kg,kb;
    std::cout<<"kr: \n";
    std::cin>>kr;
    std::cout<<"kg: \n";
    std::cin>>kg;
    std::cout<<"kb: \n";
    std::cin>>kb;
    material->setKd(DifuseReflectiveness(Coeficients(kr,kg,kb)));
    flag = true;
  }
  else if(option == 3){
    double kr,kg,kb,shininess;
    std::cout<<"kr: \n";
    std::cin>>kr;
    std::cout<<"kg: \n";
    std::cin>>kg;
    std::cout<<"kb: \n";
    std::cin>>kb;
    std::cout<<"shininess: \n";
    std::cin>>shininess;
    material->setKe(SpecularReflectiveness(Coeficients(kr,kg,kb),shininess));
    flag = true;

  }
  return flag;

  

  
}

bool menuMaterial(Mesh * mesh){
  int option;
  bool flag = false;
  Material * material = mesh->getMaterial();
  std::cout<<material;
  std::cout<<"(1)Change Ka\n";
  std::cout<<"(2)Change Kd\n";
  std::cout<<"(3)Change Ke\n";
  std::cout<<"(4)Exit\n";
  std::cin>>option;
  if(option == 1){
    double kr,kg,kb;
    std::cout<<"kr: \n";
    std::cin>>kr;
    std::cout<<"kg: \n";
    std::cin>>kg;
    std::cout<<"kb: \n";
    std::cin>>kb;
    material->setKa(AmbientReflectiveness(Coeficients(kr,kg,kb)));
    flag = true;

  }
  else if(option == 2){
    double kr,kg,kb;
    std::cout<<"kr: \n";
    std::cin>>kr;
    std::cout<<"kg: \n";
    std::cin>>kg;
    std::cout<<"kb: \n";
    std::cin>>kb;
    material->setKd(DifuseReflectiveness(Coeficients(kr,kg,kb)));
    flag = true;
  }
  else if(option == 3){
    double kr,kg,kb,shininess;
    std::cout<<"kr: \n";
    std::cin>>kr;
    std::cout<<"kg: \n";
    std::cin>>kg;
    std::cout<<"kb: \n";
    std::cin>>kb;
    std::cout<<"shininess: \n";
    std::cin>>shininess;
    material->setKe(SpecularReflectiveness(Coeficients(kr,kg,kb),shininess));
    flag = true;

  }
  return flag;
}

bool menuLight(){
  int size = scene->getNumberOfLights();
  bool flag = false;
  int option;
  std::cout<<"Choose a Light\n";
  for(int i = 0;i<size;i++){
    std::cout<<"("<<i+1<<")"<<scene->getLightAt(i)->getName() <<"\n";
  }
  std::cin>>option;
  if(option<size+1 && option > 0){
    flag = menuChangeLight(scene->getLightAt(option-1));
  }
  else{
    std::cout<<"escolha inválida\n";
  }
  return flag;
}

void menuMain(){
  int option;
  bool flag = false;
  std::cout<<"Chose any option: \n";
  std::cout<<"(1)See Lights.\n";
  std::cout<<"(2)See Camera.\n";
  std::cout<<"(3)Set Projection.\n";
  std::cout<<"Option: \n";
  std::cin >> option;
  std::cout<< "\n" << std::flush;
  if(option == 1){
    flag = menuLight();
  }
  else{
  }
  if(flag){
    run();
    std::cout<<"Success\n";
  }
  else{
    std::cout<<"Nothing done\n";
  }
}

bool menuShape(Shape3D * shape){
  int option;
  bool flag= false;
  std::cout<< shape->getName();
  std::cout<<"\nChoose any option: \n";
  std::cout<<"(1)Apply Transform.\n"; //ok
  std::cout<<"(2)Change Material.\n";
  std::cout<<"(3)Exit.\n";    
  std::cin>>option;
  if(option == 1){
    flag = menuTransform(shape);
  }
  else if(option == 2){
    flag = menuMaterial(shape);
  }
  return flag;

}

bool ShapeListMenu(Object * clickedObj){
  int size = clickedObj->getShapeCount();
  bool flag = false;
  int option;
  std::cout<<"Choose a shape\n";
  for(int i = 0;i<size;i++){
    std::cout<<"("<<i+1<<")"<<clickedObj->getShapeAt(i)->getName() <<"\n";
  }
  std::cin>>option;
  if(option<size+1 && option > 0){
    flag = menuShape(clickedObj->getShapeAt(option-1));
  }
  else{
    std::cout<<"escolha inválida\n";
  }
  return flag;
}

bool menuObj(Object * clickedObj){
  int option;
  bool flag = false;
  std::cout<< clickedObj->getName();
  std::cout<<"\nChoose any option: \n";
  std::cout<<"(1)Apply Transform.\n"; //ok
  std::cout<<"(2)See shapes.\n";
  std::cout<<"(3)See meshes.\n";
  std::cout<<"(9)Sair.\n";
  std::cout<<"Option: \n";
  std::cin >> option;
  //std::cout<< "\n" << std::flush;
  if(option == 1){
    flag = menuTransform(clickedObj);
  }
  else if(option == 2){
    flag = ShapeListMenu(clickedObj);
  }
  //glfwPostEmptyEvent();
  //return 1;
  return flag;
}

void setGlfw(){
  glfwSetErrorCallback(ErrorCallback);
  if (!glfwInit()) {
      std::cout<< "Couldn't init GLFW\n";
      exit(-1);
  }
  window = glfwCreateWindow(nLines, nColumns, "CG", NULL, NULL);
  if (!window) {
      std::cout<<"Couldn't open window\n";
      exit(-1);
  }
  glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
  glfwMakeContextCurrent(window);
  glfwSetMouseButtonCallback(window,mouseButtonCallback);
  glfwWaitEventsTimeout(30);
  uint8_t * data = canvas->getColorBuffer();
  glGenTextures(1, &tex_handle);
  glBindTexture(GL_TEXTURE_2D, tex_handle);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nLines, nColumns, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void display(){
  uint8_t * data = canvas->getColorBuffer();
  glfwMakeContextCurrent(window);
  while (!glfwWindowShouldClose(window)) {
    //glfwMakeContextCurrent(window);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nLines, nColumns, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     // Set up orphographic projection
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, 0, window_height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    // Render whatever you want
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glBegin(GL_QUADS);
      glTexCoord2d(0,1); glVertex2i(0, 0);
      glTexCoord2d(1,1); glVertex2i(nLines, 0);
      glTexCoord2d(1,0); glVertex2i(nLines,nColumns);
      glTexCoord2d(0,0); glVertex2i(0, nColumns);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glfwSwapBuffers(window);
    //glfwPollEvents();
  }
}

int main() {
  double wj = 60;
  double hj = 60;
  double canvasDistance = -30;
  double dx = wj / nColumns;
  double dy = hj / nLines;

  scene = new Scene();
  
  constructScene();
  // Canvas creation
  canvas = new Canvas<nLines,nColumns>();
  canvas->setCanvasDistance(-30);
  canvas->setGridSize({dx,dy});
  canvas->setWindowsSize({wj,hj});
  
  //Canvas Loop
  run();
  setGlfw();
  glfwMakeContextCurrent(NULL);
  std::thread renderThread(display);
  while (true) {
    glfwPollEvents();
  }
  renderThread.join();

  

  //Write to file(will be changed)
  //writePPM<nLines,nColumns>(canvas);

  return 0;
}