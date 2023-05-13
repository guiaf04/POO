//Fiz tudo sozinho e passou em todos os casos
//Levei em média 1 hora
//Aprendi o conceito de mapeamento
#include <fn.hpp>
#include <iostream>

using namespace std;

class Fone {
  std::string id;
  std::string number;

public:
  Fone(std::string id = "", std::string number = "") {
    this->id = id;
    this->number = number;
  }
  std::string getId() {
    return this->id; // todo
  }
  std::string getNumber() {
    return this->number; // todo
  }
  bool isValid() {
    string valid = "0123456789().";
    int count = 0;
    for(auto elem : number){
      for(int i = 0; i < valid.size(); i++){
        if(elem == valid[i]){
          count++;
        }
      }

      if(count == 0){
        return false;
      }
      count = 0;
    }
    return true;
  }
  std::string str() {
    if (this->id == "") {
      return "";
    } else {
      return this->id + ":" + this->number;
    }
  }
};

class Contact {
  std::string name;
  bool favorited;
  std::vector<Fone> fones;

public:
  Contact(std::string name = "") { // todo
    this->name = name;
    favorited = false;
  }

  std::string getName() {
    return this->name; // todo
  }

  std::vector<Fone> getFones() {
    return fones; // todo
  }

  void addFone(std::string id, std::string number) {
    if(Fone(id, number).isValid()){
      fones.push_back(Fone(id, number));
    }else{
      cout << "fail: invalid number" << endl;
    }
  }

  void rmFone(int index) {
    if (index >= 0 && index < fones.size()) {
      std::vector<Fone> newfone;
      for(int i = 0; i < fones.size(); i++){
        if(i != index){
          newfone.push_back(fones[i]);
        }
      }
      fones = newfone;
    }
  }

  void toogleFavorited() {
    if(isFavorited()){
      favorited = false;
    }else{
      favorited = true;
    }
  }

  bool isFavorited() {
    return favorited; // todo
  }

  std::string str() {
    auto aux = (isFavorited() ? "@ " : "- ") + name + " [";
    if (fones.size() == 0) {
      aux += "]";
    } else {
      for (int i = 0; i < (int)fones.size(); i++) {
        aux += fones[i].str();
        if (i != (fones.size() - 1)) {
          aux += ", ";
        }
      }
      aux += "]";
    }

    return aux;
  }
};

std::ostream &operator<<(std::ostream &out, Contact contato) {
  return out << contato.str();
}
std::ostream &operator<<(std::ostream &out, Fone fone) {
  return out << fone.str();
}

int main() {
  Contact contato;
  while (true) {
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line, ' ');

    if (args[0] == "end") {
      break;
    } else if (args[0] == "init") { // name
      contato = Contact(args[1]);
    } else if (args[0] == "add") { // id fone
      contato.addFone(args[1], args[2]);
    } else if (args[0] == "rm") { // id
      contato.rmFone(+args[1]);
    } else if (args[0] == "tfav") {
      contato.toogleFavorited();
    } else if (args[0] == "show") {
      fn::write(contato);
    } else {
      fn::write("fail: comando invalido");
    }
  }
}