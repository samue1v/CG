// Online C++ compiler to run C++ program online
#include <iostream>
#include <unistd.h>

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
    Nome * nome = new Nome();
    nome->addNome(1);
    legal(nome);
    return 0;
}