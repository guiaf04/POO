//1.Fiz tudo sozinho, no replit, mas tive ajuda do professor na criação
//de um novo elemento no método reserva
//2.Passou em todos os casos de teste
//3.Levei em média 1h
//4.Aprendi a manipular ponteiros e tomar cuidado no acesso de nulos

#include <fn.hpp>
#include <iostream>

using namespace std;

struct Cliente{
  std::string id;
  std::string fone;

public:
  Cliente(std::string id = "", std::string fone = "") {
    this->id = id;
    this->fone = fone;
  }

  string getFone(){
    return this->fone;
  }

  string getId(){
    return this->id;
  }

  void setFone(string fone){
    this->fone = fone;
  }

  void setId(string id){
    this->id = id;
  }

  std::string str() {
      return this->id + ":" + this->fone;
  }
};

std::ostream& operator<<(std::ostream& os, Cliente c) {
    return os << c.str();
}

class Sala{
  std::vector<std::shared_ptr<Cliente>> cadeiras;

  int procurar(std::string nome) {
    int aux = -1;
    for(int i = 0; i < cadeiras.size(); i++){
      if(cadeiras[i] != nullptr){
        if(cadeiras[i]->getId() == nome){
          aux = i;
        }
      }
    }
    return aux; // todo
  }

  bool verificarIndice(int indice){
    return indice < cadeiras.size();
  }

public:
  Sala(int qtd = 0) {
    for(int i = 0; i < qtd; i++){
      cadeiras.push_back(nullptr);
    }
  }

  void reservar(std::string id, std::string fone, int ind) {
    if(verificarIndice(ind)){
      if(cadeiras[ind] != nullptr){
        cout << "fail: cadeira ja esta ocupada"<< endl;
      }else if((procurar(id)) != -1){
        cout << "fail: cliente ja esta no cinema" << endl;
      }else{
        cadeiras[ind] = make_shared<Cliente>(id, fone);
      } 
    }else{
      cout << "fail: cadeira nao existe" << endl;
    }
  }

  void cancelar(std::string id) {
    int aux = procurar(id);
    
    if(aux != -1){
      cadeiras[aux] = nullptr;
    }else{
      cout << "fail: cliente nao esta no cinema" << endl;
    }
  }

  std::string str() {
    string aux = "[";

    for(unsigned int i = 0; i < cadeiras.size();i++){
      if(i == 0){
        if(cadeiras[i] == nullptr){
          aux += "-";
        }else{
          aux += cadeiras[i]->str();
        }
      }else{
        if(cadeiras[i] == nullptr){
          aux += " -";
        }else{
          aux += " ";
          aux += cadeiras[i]->str();
        }
      }
    }
    aux += "]";
    
    return aux; // todo
  }
};

std::ostream& operator<<(std::ostream& os, Sala c) {
    return os << c.str();
}


int main() {
    Sala sala;
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "show") {
            fn::write(sala);
        } else if (args[0] == "init") {
            sala = Sala(+args[1]);
        } else if (args[0] == "reservar") {
            sala.reservar(args[1], args[2], (int) +args[3]);
        } else if (args[0] == "cancelar") {
            sala.cancelar(args[1]);
        } else {
            fn::write("fail: comando invalido");
        }
    }
}

