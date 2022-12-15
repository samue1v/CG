// Online C++ compiler to run C++ program online
#include <iostream>
#include <unistd.h>
#include "../DataStructures/Array.h"

class Nome{
  private:
  int nomereal;
  public:
  Nome(){

  }
  int getNome(){
      return nomereal;
  }
  void addNome(int nome){
      this->nomereal += nome;
  }
};


void update(Nome * nome){
    nome->addNome(1);
}


void legal(Nome * nomep){
    int cont =  0;
    for(int i = 0;i<50;i++){
        std::cout<< nomep->getNome() <<"\n";
        sleep(1);
        if(cont%2 == 1){
            update(nomep);
        }
        
    }
}

int main() {
    Array<double> a;
    Array<double> b;
    a.push(1);
    a.push(2);
    b = a;
    a.push(3);
    std::cout<<"a:"<<a<<"\n";
    std::cout<<"b:"<<b<<"\n";
    return 0;
}