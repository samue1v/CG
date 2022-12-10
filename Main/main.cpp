/*
Lembrar de olhar o calculo da normal da malha, lembra da ordem g o f
lembra que eu mudei canvas distance pra ser positivo, logo no loop principal deve-se mudar
para -canvas_distance
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
#include "../libs/glfw/include/GLFW/glfw3.h"
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>
#include <SDL2/SDL_image.h>

template<int l,int k>
bool writePPM(Canvas<l,k> *canvas) {
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

void constructScene(Scene & scene){
  SDL_Renderer * renderer = nullptr;
  double sphereDistance = 60;

  Coordinate eye = Coordinate(0,0,70);
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

  //Sphere
  Sphere *circle = new Sphere(Coordinate(0,0,-10), 1, rubber);
  //circle->setTransform(new Scale(0.5,1,1));
  //circle->setTransform(new Translate(50,10,-100));
  

  //Cylinder
  Vector3D cylinderAxis = Vector3D(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
  Cylinder * cylinder = new Cylinder(Coordinate(10,0,-100),Vector3D(1,0,0),20,50,marble);
  Coordinate cylinderTop = (cylinderAxis*3*radius)+center;

  //cylinder->setTransform(new RotateX(120));
  //cylinder->setTransform(new Translate(120,90,-60));
  //cylinder->setTransform(new Scale(2,3,3));
  
  
  //Cone
  double coneRadius = 1.5*radius;
  //Cone * cone = new Cone(cylinderTop,cylinderAxis,coneRadius,coneRadius/3,marble);
  Cone * coneup = new Cone(Coordinate(0,10,-100),Vector3D(0,1,0),10,20,marble);
  Cone * conedown = new Cone(Coordinate(0,-10,-100),Vector3D(0,-1,0),10,20,rubber);
  Cone * coneleft = new Cone(Coordinate(-10,0,-100),Vector3D(-1,0,0),10,20,marble);
  Cone * coneright = new Cone(Coordinate(10,0,-100),Vector3D(1,0,0),10,20,marble);
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
  std::string simple_mesh = "../MeshFiles/cube.obj";
  std::string casa_mesh = "../MeshFiles/casa.obj";
  std::string quadro_mesh = "../MeshFiles/frame.obj";
  Mesh * mesh = new Mesh(quadro_mesh,marble);

  //Mesh * mesh = new Mesh(casa_mesh,marble);
  mesh->setTransform(new Translate(25,0,0));
  mesh->setTransform(new Scale(0.8,0.8,0.8));
  //mesh->setTransform(new Scale(20,20,20));
  //mesh->setTransform(new RotateY(-135));
  //mesh->setTransform(new RotateX(-135));
  //mesh->setTransform(new RotateZ(30));
  //mesh->setTransform(new ShearYX(30));
  
  mesh->setTexture("../TextureFiles/kaguya.png",renderer);

  //Object
  char name[] = "circulo";
  char plano[] = "plane";
  //Object *obj = new Object(name,  3);
  Object *obj = new Object(name);
  Object *objPlane = new Object(plano);

  //Setting shapes and meshes to object

  //obj->setShape(circle);
  //obj->setShape(floorPlane);
  //obj->setShape(backPlane);
  obj->setMesh(mesh);
  //obj->setShape(cylinder);
  //obj->setShape(coneleft);  
  //obj->setShape(coneright);
  //obj->setShape(coneup);
  //obj->setShape(conedown);


  objPlane->setShape(floorPlane);

 // obj->setTransform(new RotateZ(45));
  //obj->setTransform(new Translate(0,10,50));
  obj->setTransform(new Scale(20,20,20));
  
  obj->setTransform(new RotateYfixed(180,Coordinate(0,0,-10)));
  obj->setTransform(new RotateXfixed(30,Coordinate(0,0,-10)));
  obj->setTransform(new RotateY(360));
  //obj->setTransform(new RotateYfixed(-90,Coordinate(0,0,-100)));
  //obj->setTransform(new Translate(20,20,20));
  //obj->setTransform(new Scale(5,50,50));


  
  //Setting lights

  Intensity ambientIntensity = Intensity(0.2, 0.2, 0.2);
  AmbientLight *ambientLight = new AmbientLight(ambientIntensity);
  Intensity pointIntensity = Intensity(0.7, 0.7, 0.7);
  PointLight *pointLight =new PointLight(pointIntensity, Coordinate(0,0,70));//Coordinate(0,60,-30))
  PointLight *pointLight2 =new PointLight(pointIntensity, Coordinate(0,200 ,1000));
  DirectionalLight * dirLight = new DirectionalLight(Intensity(0.2,0.2,0.2),Vector3D(0,0,-1));
  //Creating the scene
  
  scene.setObject(obj);
  //scene.setObject(objPlane);



  scene.setLight(ambientLight);
  //scene->setLight(dirLight);
  //scene.setLight(pointLight);
  scene.setLight(pointLight2);
  scene.setCamera(camera);
  scene.transformView();
  
}

template<int nLines,int nColumns>
void run(Scene * scene,Canvas<nLines,nColumns> * canvas){
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
      canvas->setObjectAt(l,c,hitData.left);
      if(hitData.right.hasInit){
        canvas->pushColorBuffer(hitData.right * hitData.middle);
      }
      else{
        canvas->pushColorBuffer(scene->getNaturalColor() * hitData.middle);
      }
    }
  }
}

void ErrorCallback(int, const char* err_str)
{
    std::cout << "GLFW Error: " << err_str << std::endl;
}

template<int nLines,int nColumns>
void display(Canvas<nLines,nColumns> * canvas){
  GLFWwindow* window;
  
  glfwSetErrorCallback(ErrorCallback);
  if (!glfwInit()) {
      std::cout<< "Couldn't init GLFW\n";
      exit(-1);
  }

  window = glfwCreateWindow(nLines, nColumns, "CG", NULL, NULL);
  glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
  if (!window) {
      std::cout<<"Couldn't open window\n";
      exit(-1);
  }


    glfwMakeContextCurrent(window);
    uint8_t * data = canvas->getColorBuffer();
    GLuint tex_handle;
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nLines, nColumns, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  while (!glfwWindowShouldClose(window)) {
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
      glTexCoord2d(1,1); glVertex2i(0 + nLines, 0);
      glTexCoord2d(1,0); glVertex2i(0 + nLines /** 2*/, 0 + nColumns /** 2*/);
      glTexCoord2d(0,0); glVertex2i(0, 0 + nColumns /** 2*/);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glfwSwapBuffers(window);
    glfwWaitEvents();
    }

}

int main() {
  double wj = 60;
  double hj = 60;
  double canvasDistance = -30;
  const int nLines = 600;
  const int nColumns = 600;
  double dx = wj / nColumns;
  double dy = hj / nLines;

  Scene * scene = new Scene;
  
  constructScene(*scene);

  // Canvas creation
  Canvas<nLines,nColumns> *canvas = new Canvas<nLines,nColumns>();
  canvas->setCanvasDistance(-30);
  canvas->setGridSize({dx,dy});
  canvas->setWindowsSize({wj,hj});
  
  //Canvas Loop
  run<nLines,nColumns>(scene,canvas);
  display<nLines,nColumns>(canvas);
  //Write to file(will be changed)
  //writePPM<nLines,nColumns>(canvas);

  return 0;
}