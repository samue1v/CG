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

const int nLines = 500;
const int nColumns = 500 ;

Canvas<nLines,nColumns> * canvas;
Scene * scene;
GLFWwindow* window;
GLuint tex_handle;

void setGlfw();
void display();
void constructScene();
void run();
bool menuObj(Object *);
bool menuMain();
bool shapeListMenu(Object *);
bool MeshListMenu(Object *);
bool menuMesh(Mesh *);
bool menuShape(Shape3D *);
bool menuTransform(Object *);
bool menuTransform(Shape3D *);
bool menuTransform(Mesh *);
bool menuTransform(Camera *);
bool menuMaterial(Object *);
bool menuMaterial(Shape3D *);
bool menuMaterial(Mesh *);
bool menuTransform(Light * light);

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
  float sphereDistance = 60;

  Coordinate eye = Coordinate(10,0,5);
  Coordinate up = Coordinate(10,20,5);
  Coordinate lookAt = Coordinate(10,0,-100);  

  Camera * camera  = new Camera(eye,lookAt,up);

  // inicialização da cena e da esfera
  float radius = 100;

  Coordinate center = Coordinate(0, 0, -(sphereDistance + radius));

  

  //Materials
  Rubber * rubber =new Rubber();
  Metal * metal = new Metal();
  Plastic * plastic = new Plastic();
  Copper * copper = new Copper();
  Marble * marble = new Marble();
  Wood * wood = new Wood();
  Brick * brick = new Brick();
  BlueConcrete * blueconcrete = new BlueConcrete();


  //testes
  /*
  Object * teste = new Object("teste");
  Mesh * cluster_teste_mesh = new Mesh("../MeshFiles/paredes_cluster.obj",marble,"paredes_mesh");
  teste->setMesh(cluster_teste_mesh);
  */
 
  //globo
  Cylinder * globoBase = new Cylinder(Coordinate(-6,-5.5,6),Vector3D(0,1,0),2,10.6,metal,"base lampada.");
  Object * globo = new Object("globo");
  Sphere * globo_sphere = new Sphere(Coordinate(10,-2.36,1.6),1,plastic,"globo");
  //globo_sphere->setTexture("../TextureFiles/world.png",renderer);
  globo->setShape(globo_sphere);
  globo->setShape(globoBase);

  //casa
  Object * paredes = new Object("paredes");
  Mesh * paredes_mesh = new Mesh("../MeshFiles/paredes_novas2.obj",marble,"paredes_mesh");
  Mesh * parede_azul = new Mesh("../MeshFiles/parede_azul.obj",blueconcrete,"parede_azul");
  //Mesh * muros = new Mesh("../MeshFiles/muros.obj",marble,"muros");
  Mesh * teto = new Mesh("../MeshFiles/teto.obj",marble,"teto");
  Mesh * tetocima = new Mesh("../MeshFiles/tetocima.obj",marble,"teto");
  Mesh * porta_entrada = new Mesh("../MeshFiles/porta_entrada.obj",marble,"porta entrada");
  Mesh * porta_saida = new Mesh("../MeshFiles/porta_saida.obj",marble,"porta saida");
  porta_entrada->setTexture("../TextureFiles/porta.png",renderer);
  porta_saida->setTexture("../TextureFiles/porta.png",renderer);
  paredes_mesh->setCluster(new Mesh("../MeshFiles/paredes_cluster.obj"));
  paredes->setMesh(paredes_mesh);
  paredes->setMesh(parede_azul);
  paredes->setMesh(porta_entrada);
  paredes->setMesh(porta_saida);

  //paredes->setMesh(muros);
  paredes->setMesh(tetocima);
  paredes->setMesh(teto);

  Object * ground = new Object("ground");
  Plane * groundPlane = new Plane(Coordinate(0,-4.95,0),Vector3D(0,1,0),marble,"groundplane");
  groundPlane->setTexture("../TextureFiles/grass.png",renderer);
  ground->setShape(groundPlane);



  //solo
  Object * piso = new Object("piso");
  Mesh * piso_mesh = new Mesh("../MeshFiles/piso.obj",marble,"piso mesh");
  piso_mesh->setTexture("../TextureFiles/carpete.png",renderer);
  piso->setMesh(piso_mesh);

  //quadro1
  Object * quadro1 = new Object("quadro1");
  Mesh * frame1 = new Mesh("../MeshFiles/frame123.obj",plastic,"frame1");
  frame1->setTransform(new RotateZ(180));
  frame1->setTransform(new Scale(1.023,1,1));
  frame1->setTexture("../TextureFiles/notRep_rene.png",renderer);
  frame1->setTransform(new Translate(2.76,0,-9.1));
  Mesh * moldura1 = new Mesh("../MeshFiles/moldura123.obj",wood,"moldura1");
  moldura1->setTexture("../TextureFiles/wood_moldura.png",renderer);
  moldura1->setCluster(new Mesh("../MeshFiles/moldura123_cluster.obj"));
  moldura1->setTransform(new Translate(2.8,0,-9.1));
  quadro1->setMesh(moldura1);
  quadro1->setMesh(frame1);

  


  Object * quadro2 = new Object("quadro2");
  Mesh * frame2 = new Mesh("../MeshFiles/frame123.obj",plastic,"frame2");
  frame2->setTransform(new RotateZ(180));
  frame2->setTransform(new Scale(1.023,1,1));
  frame2->setTexture("../TextureFiles/reve_picasso.png",renderer);
  frame2->setTransform(new Translate(10.2,0,-9.1));
  Mesh * moldura2 = new Mesh("../MeshFiles/moldura123.obj",wood,"moldura2");
  moldura2->setTexture("../TextureFiles/wood_moldura.png",renderer);
  moldura2->setCluster(new Mesh("../MeshFiles/moldura123_cluster.obj"));
  moldura2->setTransform(new Translate(10.2,0,-9.1));
  quadro2->setMesh(moldura2);
  quadro2->setMesh(frame2);


  Object * quadro3 = new Object("quadro3");
  Mesh * frame3 = new Mesh("../MeshFiles/frame123.obj",plastic,"frame3");
  frame3->setTransform(new RotateZ(180));
  frame3->setTransform(new Scale(1.023,1,1));
  frame3->setTexture("../TextureFiles/filho_rene.png",renderer);
  frame3->setTransform(new Translate(17.7,0,-9.1));
  Mesh * moldura3 = new Mesh("../MeshFiles/moldura123.obj",wood,"moldura3");
  moldura3->setTexture("../TextureFiles/wood_moldura.png",renderer);
  moldura3->setCluster(new Mesh("../MeshFiles/moldura123_cluster.obj"));
  moldura3->setTransform(new Translate(17.7,0,-9.1));
  quadro3->setMesh(moldura3);
  quadro3->setMesh(frame3);


  //quadro4
  Object * quadro4 = new Object("quadro4");
  Mesh * frame4 = new Mesh("../MeshFiles/frame45.obj",plastic,"frame4");
  frame4->setTexture("../TextureFiles/guernica_picasso.png",renderer);
  frame4->setTransform(new RotateX(180));
  frame4->setTransform(new Scale(1.023,1,1));
  frame4->setTransform(new Translate(22.3,0,-4.4));
  Mesh * moldura4 = new Mesh("../MeshFiles/moldura45.obj",wood,"moldura4");
  moldura4->setTexture("../TextureFiles/wood_moldura.png",renderer);
  moldura4->setCluster(new Mesh("../MeshFiles/moldura45_cluster.obj"));
  moldura4->setTransform(new Translate(22.3,0,-4.4));
  quadro4->setMesh(moldura4);
  quadro4->setMesh(frame4);

  
    //quadro5
  Object * quadro5 = new Object("quadro4");
  Mesh * frame5 = new Mesh("../MeshFiles/frame45.obj",plastic,"frame5");
  frame5->setTexture("../TextureFiles/memoria_dali.png",renderer);
  frame5->setTransform(new RotateX(180));
  frame4->setTransform(new Scale(1.023,1,1));
  frame5->setTransform(new Translate(22.3,0,4.4));
  Mesh * moldura5 = new Mesh("../MeshFiles/moldura45.obj",wood,"moldura5");
  moldura5->setTexture("../TextureFiles/wood_moldura.png",renderer);
  moldura5->setCluster(new Mesh("../MeshFiles/moldura45_cluster.obj"));
  moldura5->setTransform(new Translate(22.3,0,4.4));
  quadro5->setMesh(moldura5);
  quadro5->setMesh(frame5);
  
  //banco longo1
  Object * bancoLongo1 = new Object("banco longo1");
  Mesh * banco_longo1_mesh = new Mesh("../MeshFiles/banco_longo.obj",wood,"banco longo 1 mesh");
  banco_longo1_mesh->setTexture("../TextureFiles/banco_longo.png",renderer);
  banco_longo1_mesh->setCluster(new Mesh("../MeshFiles/banco_longo_cluster.obj"));
  banco_longo1_mesh->setTransform(new Translate(16.4,-4,2));
  bancoLongo1->setMesh(banco_longo1_mesh);
  
  
  //banco longo2
  Object * bancoLongo2 = new Object("banco longo2");
  Mesh * banco_longo2_mesh = new Mesh("../MeshFiles/banco_longo2.obj",wood,"banco longo 2 mesh");
  banco_longo2_mesh->setTexture("../TextureFiles/banco_longo.png",renderer);
  banco_longo2_mesh->setCluster(new Mesh("../MeshFiles/banco_longo2_cluster.obj"));
  banco_longo2_mesh->setTransform(new Translate(10,-4,-3.7));
  bancoLongo2->setMesh(banco_longo2_mesh);

  //banco pequeno
  Object * bancoPequeno = new Object("banco pequeno");
  Mesh * banco_pequeno_mesh = new Mesh("../MeshFiles/banco_bar.obj",wood,"banco pequeno mesh");
  //banco_pequeno_mesh->setTexture("../TextureFiles/banco_bar.png",renderer);
  banco_pequeno_mesh->setCluster(new Mesh("../MeshFiles/banco_bar_cluster.obj"));
  banco_pequeno_mesh->setTransform(new Translate(10,-3.36,1.6));
  bancoPequeno->setMesh(banco_pequeno_mesh);






  
  //Setting lights
  
  Intensity ambientIntensity = Intensity(0.2, 0.2, 0.2);
  AmbientLight *ambientLight = new AmbientLight(ambientIntensity,"Ambiente Light");
  /*
  Intensity pointIntensity = Intensity(0.7, 0.7, 0.7);
  //SpotLight * spottlight = new SpotLight(pointIntensity,Coordinate(0,20,5),Vector3D(0,-1,0),20,"spot");
  PointLight *pointLight =new PointLight(pointIntensity, Coordinate(0,1.4,5),"PointLight");//Coordinate(0,60,-30))
  //PointLight *pointLight2 =new PointLight(pointIntensity, Coordinate(0,200 ,1000));
  PointLight *pointLight3 =new PointLight(pointIntensity, Coordinate(0,0,0),"PointLight3");
  DirectionalLight * dirLight = new DirectionalLight(Intensity(0.6,0.6,0.6),Vector3D(0,-1,-1),"DirLIght");
  */

  SpotLight * spot1 = new SpotLight(Intensity(0.9,0.9,0.9),Coordinate(2.8,4.5,-6.5),Vector3D(0,-0.7,-1),20,"spot1");
  SpotLight * spot2 = new SpotLight(Intensity(0.9,0.9,0.9),Coordinate(10.2,4.5,-6.5),Vector3D(0,-0.7,-1),20,"spot2");
  SpotLight * spot3 = new SpotLight(Intensity(0.9,0.9,0.9),Coordinate(17.6,4.5,-6.5),Vector3D(0,-0.7,-1),20,"spot3");
  SpotLight * spot4 = new SpotLight(Intensity(0.9,0.9,0.9),Coordinate(18.2,4.2,-4.5),Vector3D(1,-0.6,0),15,"spot4");
  SpotLight * spot5 = new SpotLight(Intensity(0.9,0.9,0.9),Coordinate(18.2,4.2,4.5),Vector3D(1,-0.6,0),15,"spot5");
  
  //PointLight * pointmiddle = new PointLight(Intensity(0.7,0.7,0.7),Coordinate(10,4.8,1.6),"pointlightmiddle");
  PointLight * pointmiddle = new PointLight(Intensity(0.7,0.7,0.7),Coordinate(10,0,10),"pointlightmiddle");
  PointLight * pointdoor = new PointLight(Intensity(0.4,0.4,0.4),Coordinate(-9.63, 4.8, -6),"pointlightdoor");
  DirectionalLight * dirLight = new DirectionalLight(Intensity(0.5,0.5,0.5),Vector3D(0,-1,-0.1),"DirLIght");
  //Creating the scene
  
  scene->setObject(paredes);
  scene->setObject(quadro1);
  scene->setObject(quadro2);
  scene->setObject(quadro3);
  scene->setObject(quadro4);
  scene->setObject(quadro5);
  scene->setObject(bancoLongo1);
  scene->setObject(bancoLongo2);
  scene->setObject(bancoPequeno);
  scene->setObject(globo);
  scene->setObject(piso);
  
  scene->setObject(ground);



  scene->setLight(ambientLight);
  scene->setLight(spot1);
  scene->setLight(spot2);
  scene->setLight(spot3);
  scene->setLight(spot4);
  scene->setLight(spot5);
  scene->setLight(pointmiddle);
  //scene->setLight(pointdoor);
  scene->setLight(dirLight);
  //scene->setLight(pointLight);
  //scene.setLight(pointLight2);
  //scene->setLight(spottlight);
  //scene->setLight(pointLight3);
  scene->setCamera(camera);
  //lamp->setTransform(new Translate(10,0,0));
  scene->transformWorldToCamera();
  
}

void run(){
  Vector3D dr;
  Vector3D orthoDir = Vector3D(0,0,-1);
  Vector3D ortho = (scene->getCamera()->getWorldToCamera() * Matrix<float,4,1>(orthoDir)).toVector3D() ;
  Coordinate canvasPoint;
  Pair<float,float> windowSize = canvas->getWindowSize();
  float wj = windowSize.left;
  float hj = windowSize.right;
  Pair<float,float> gridSize = canvas->getGridSize();
  float dx = gridSize.left;
  float dy = gridSize.right;
  bool isO = canvas->isOrtho;
  if(isO){
    wj = 60;
    hj = 60;
    dx = wj/nColumns;
    dy = hj/nLines;
  }
  Coordinate P0 = scene->getCamera()->getEyeTransformed();
  canvas->clearCanvas();
  for (int l = 0; l < nLines; l++) {
    float y = hj / 2 - dy / 2 - l * dy;
    for (int c = 0; c < nColumns; c++) {
      float x = -wj / 2 + dx / 2 + c * dx;
      canvasPoint = Coordinate(x, y, canvas->getCanvasDistance());
      if(isO){
        dr = ortho;
        P0 = canvasPoint;
      }
      else{
        dr= Vector3D(canvasPoint - P0);
        dr.normalize();
      }
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
       if(obj){
        obj->applyViewTransform(scene->getCamera()->getCameraToWorld());
        flag = menuObj(obj);
        obj->applyViewTransform(scene->getCamera()->getWorldToCamera());
       }
       else{
        std::cout<<"ceu.\n";
        flag = false;
       }
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
      flag = menuMain();
      if(flag){
        run();
        std::cout<<"Success\n";
      }
      else{
        std::cout<<"Nothing done.\n";
      }
       
    }

}

bool menuChangeLight(Light * light){
  int option;
  bool flag = false;
  std::cout<<"Chose any option: \n";
  std::cout<<"(1)Flip Switch.\n";
  std::cout<<"(2)Transform.\n";
  std::cout<<"(3)Change Intensity.\n";
  std::cout<<"(4)Exit.\n";
  std::cout<<"Option: \n";
  std::cin >> option;
  if(option == 1){
    light->flipSwitch();
    flag = true;
  }
  else if(option == 2){
      flag = menuTransform(light);
  }
  else if(option == 3){
    float ir,ig,ib;
    std::cout<<"Digite o valor de ir: \n";
    std::cin>>ir;
    std::cout<<"Digite o valor de ig: \n";
    std::cin>>ig;
    std::cout<<"Digite o valor de ib: \n";
    std::cin>>ib;
    light->setIntensity(Intensity(ir,ig,ib));
    flag = true;
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
    float x,y,z;
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
    float x,y,z;
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
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateX(degree));
    flag =  true;


  }
  else if(option == 4){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateY(degree));
    flag = true;

  }
  else if(option == 5){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateZ(degree));
    flag = true;

  }
  else if(option == 6){
    float degree,x,y,z;
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
    float degree,x,y,z;
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
    float degree,x,y,z;
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
    float x,y,z;
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
    float x,y,z;
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
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateX(degree));
    flag = true;


  }
  else if(option == 4){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateY(degree));
    flag = true;
  }
  else if(option == 5){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateZ(degree));
    flag = true;
  }
  else if(option == 6){
    float degree,x,y,z;
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
    float degree,x,y,z;
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
    float degree,x,y,z;
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
    /*
    std::cout<<"Operação não suportada.\n";
    flag = false;
    */
   inp->setTransform(new ShearXY(45));
   flag = true;
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

bool menuTransform(Camera * camera){
  bool flag= false;
  int option;
  std::cout<<"Chose any option: \n";
  std::cout<<"(1)Apply Translate.\n";
  std::cout<<"(2)Apply RotateX.\n";
  std::cout<<"(3)Apply RotateY.\n";
  std::cout<<"(4)Apply RotateZ.\n";
  std::cout<<"(5)Exit.\n";
  std::cin>>option;
  if(option==1){
    float x,y,z;
    std::cout<<"Digite o valor de x: \n";
    std::cin>>x;
    std::cout<<"Digite o valor de y: \n";
    std::cin>>y;
    std::cout<<"Digite o valor de Z: \n";
    std::cin>>z;
    std::cout<<"\n";
    camera->setTransform(new Translate(x,y,z));
    flag = true;
  }
  else if(option == 2){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    camera->setTransform(new RotateX(degree));
    flag = true;
  }
  else if(option == 3){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    camera->setTransform(new RotateY(degree));
    flag = true;
  }
  else if(option == 4){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    camera->setTransform(new RotateZ(degree));
    flag=true;
  }
  return flag;
}

bool menuTransform(Light * light){
  bool flag = false;
  light->applyViewTransform(scene->getCamera()->getCameraToWorld());
  if(light->getLightType() == directional){
    DirectionalLight * dirlight = static_cast<DirectionalLight *>(light);
    float angle;
    int option;
    std::cout<<"Choose a transform:\n";
    std::cout<<"(1)RotateX.\n";
    std::cout<<"(2)RotateY.\n";
    std::cout<<"(3)RotateZ.\n";
    std::cin>>option;
    std::cout<<"Digite o angulo: \n";
    std::cin>>angle;
    if(option == 1){
      dirlight->setTransform(new RotateX(angle));
      flag = true;
    }
    else if(option == 2){
      dirlight->setTransform(new RotateY(angle));
      flag = true;
    }
    else if(option == 3){
      dirlight->setTransform(new RotateZ(angle));
      flag = true;
    }

  }
  else if(light->getLightType() == point){
    PointLight * plight = static_cast<PointLight*>(light);
    int option;
    std::cout<<"Choose a transform:\n";
    std::cout<<"(1)Translate";
    if(option == 1){
      float x,y,z;
      std::cout<<"Value for X:\n";
      std::cin>>x;
      std::cout<<"Value for Y:\n";
      std::cin>>y;
      std::cout<<"Value for Z:\n";
      std::cin>>z;
      plight->setTransform(new Translate(x,y,z));
      flag = true;
    }
  }
  else if(light->getLightType() == spot){
    SpotLight * splight = static_cast<SpotLight *>(light);
    int option;
    std::cout<<"Choose a transform:\n";
    std::cout<<"(1)Translate.\n";
    std::cout<<"(2)RotateX.\n";
    std::cout<<"(3)RotateY.\n";
    std::cout<<"(4)RotateZ.\n";
    std::cout<<"(5)Change angle.\n";
    std::cin>>option;
    if(option == 1){
      float x,y,z;
      std::cout<<"Value for X:\n";
      std::cin>>x;
      std::cout<<"Value for Y:\n";
      std::cin>>y;
      std::cout<<"Value for Z:\n";
      std::cin>>z;
      std::cout<<x<<"\n";
      splight->setTransform(new Translate(x,y,z));
      flag = true;
    }
    else if(option == 2){
      float angle;
      std::cout<<"Angle:\n";
      std::cin>>angle;
      splight->setTransform(new RotateX(angle));
      flag = true;
    }
    else if(option ==3){
      float angle;
      std::cout<<"Angle:\n";
      std::cin>>angle;
      splight->setTransform(new RotateY(angle));
      flag = true;
    }
    else if(option == 4){
      float angle;
      std::cout<<"Angle:\n";
      std::cin>>angle;
      splight->setTransform(new RotateZ(angle));
      flag = true;
    }
    else if(option == 5){
      float angle;
      std::cout<<"Angle:\n";
      std::cin>>angle;
      splight->setAngle(angle);
      flag = true;
    }
  }
  light->applyViewTransform(scene->getCamera()->getWorldToCamera());
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
    float x,y,z;
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
    float x,y,z;
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
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateX(degree));
    flag = true;

  }
  else if(option == 4){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateY(degree));
    flag = true;
  }
  else if(option == 5){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new RotateZ(degree));
    flag=true;

  }
  else if(option == 6){
    float degree,x,y,z;
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
    float degree,x,y,z;
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
    float degree,x,y,z;
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
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearXY(degree));
    flag = true;
  }
  else if(option == 10){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearYX(degree));
    flag = true;
  }
  else if(option == 11){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearXZ(degree));
    flag = true;
  }
  else if(option == 12){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearZX(degree));
    flag = true;
  }
  else if(option == 13){
    float degree;
    std::cout<<"Digite o valor em graus: \n";
    std::cin>>degree;
    inp->setTransform(new ShearYZ(degree));
    flag = true;
  }
  else if(option == 14){
    float degree;
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
  std::cout<<material->getName()<<"\n";
  std::cout<<"(1)Change Ka\n";
  std::cout<<"(2)Change Kd\n";
  std::cout<<"(3)Change Ke\n";
  std::cout<<"(4)Exit\n";
  std::cin>>option;
  if(option == 1){
    float kr,kg,kb;
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
    float kr,kg,kb;
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
    float kr,kg,kb,shininess;
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
  std::cout<<material->getName()<<"\n";
  std::cout<<"(1)Change Ka\n";
  std::cout<<"(2)Change Kd\n";
  std::cout<<"(3)Change Ke\n";
  std::cout<<"(4)Exit\n";
  std::cin>>option;
  if(option == 1){
    float kr,kg,kb;
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
    float kr,kg,kb;
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
    float kr,kg,kb,shininess;
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

bool menuMain(){
  int option;
  bool flag = false;
  std::cout<<"Chose any option: \n";
  std::cout<<"(1)See Lights.\n";
  std::cout<<"(2)See Camera.\n";
  std::cout<<"(3)Change Projection.\n";
  std::cout<<"(4)Change viewport distance.\n";
  std::cout<<"(5)Change window size\n";
  std::cout<<"Option: \n";
  std::cin >> option;
  std::cout<< "\n" << std::flush;
  if(option == 1){
    flag = menuLight();
  }
  else if(option == 2){
    Camera * camera = scene->getCamera();
    flag = menuTransform(camera);
    if(flag){
      scene->transformCameraToWorld();
      camera->execEyeTransform();
      scene->transformWorldToCamera();
    }
    
  }
  else if(option == 3){
    canvas->isOrtho = !canvas->isOrtho;
    flag = true;
  }
  else if(option == 4){
    float d;
    std::cout<<"New distance:\n";
    std::cin>>d;
    canvas->setCanvasDistance(d);
    flag = true;
  }
  else if(option == 5){
    float wj,hj;
    std::cout<<"New wj:\n";
    std::cin>>wj;
    std::cout<<"New hj:\n";
    std::cin>>hj;
    canvas->setWindowsSize({wj,hj});
    flag = true;
  }
  return flag;
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

bool menuMesh(Mesh * mesh){
  int option;
  bool flag= false;
  std::cout<< mesh->getName();
  std::cout<<"\nChoose any option: \n";
  std::cout<<"(1)Apply Transform.\n"; //ok
  std::cout<<"(2)Change Material.\n";
  std::cout<<"(3)Exit.\n";    
  std::cin>>option;
  if(option == 1){
    flag = menuTransform(mesh);
  }
  else if(option == 2){
    flag = menuMaterial(mesh);
  }
  return flag;
}

bool MeshListMenu(Object * clickedObj){
  int size = clickedObj->getMeshCount();
  bool flag = false;
  int option;
  std::cout<<"Choose a mesh\n";
  if(size < 1){
    std::cout<<"There is no mesh!\n";
    return flag;
  }
  for(int i = 0;i<size;i++){
    std::cout<<"("<<i+1<<")"<<clickedObj->getMeshAt(i)->getName() <<"\n";
  }
  std::cin>>option;
  if(option<size+1 && option > 0){
    flag = menuMesh(clickedObj->getMeshAt(option-1));
  }
  else{
    std::cout<<"escolha inválida\n";
  }
  return flag;
}

bool ShapeListMenu(Object * clickedObj){
  int size = clickedObj->getShapeCount();
  bool flag = false;
  int option;
  if(size < 1){
    std::cout<<"There is no shape!\n";
    return flag;
  }
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
  std::cout<<"(2)See shapes.\n";//ok
  std::cout<<"(3)See meshes.\n";//ok
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
  else if(option == 3){
    flag = MeshListMenu(clickedObj);
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
  float wj = 60;
  float hj = 60;
  float canvasDistance = -20;
  float dx = wj / nColumns;
  float dy = hj / nLines;

  scene = new Scene();
  
  constructScene();
  // Canvas creation
  canvas = new Canvas<nLines,nColumns>();
  canvas->setCanvasDistance(canvasDistance);
  //canvas->setGridSize({dx,dy});
  canvas->setWindowsSize({wj,hj});
  //exit(-1);
  
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