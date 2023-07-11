// Fiz tudo sozinho, mas tive ajuda do professor no método de ordenação
// Passou em todos os casos de teste
// Levei em média 2 horas

#include <algorithm>
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
  std::string getId() { return this->id; }
  std::string getNumber() { return this->number; }
  bool isValid() {
    string valid = "0123456789().";
    int count = 0;
    for (auto elem : number) {
      for (int i = 0; i < valid.size(); i++) {
        if (elem == valid[i]) {
          count++;
        }
      }

      if (count == 0) {
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
  Contact(std::string name = "") {
    this->name = name;
    favorited = false;
  }

  std::string getName() { return this->name; }

  std::vector<Fone> getFones() { return this->fones; }

  void setName(string name) { this->name = name; }

  void addFone(std::string id, std::string number) {
    if (Fone(id, number).isValid()) {
      fones.push_back(Fone(id, number));
    } else {
      cout << "fail: invalid number" << endl;
    }
  }

  void rmFone(int index) {
    if (index >= 0 && index < fones.size()) {
      std::vector<Fone> newfone;
      for (int i = 0; i < fones.size(); i++) {
        if (i != index) {
          newfone.push_back(fones[i]);
        }
      }
      fones = newfone;
    }
  }

  void toogleFavorited() {
    if (isFavorited()) {
      favorited = false;
    } else {
      favorited = true;
    }
  }

  bool isFavorited() { return favorited; }

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

class Agenda {
  std::vector<Contact> contatos;

  int findContact(std::string id) {

    for (int i = 0; i < contatos.size(); i++) {
      if (contatos[i].getName() == id) {
        return i;
      }
    }

    return -1;
  }

public:
  // add contato que não existe ou adicionar fones ao contato que existe
  void addContato(std::string name, std::vector<Fone> fones) {
    int index = findContact(name);
    if (index == -1) {
      Contact novo(name);
      for (int i = 0; i < fones.size(); i++) {
        novo.addFone(fones[i].getId(), fones[i].getNumber());
      }
      this->contatos.push_back(novo);
    } else {
      for (int i = 0; i < fones.size(); i++) {
        contatos[index].addFone(fones[i].getId(), fones[i].getNumber());
      }
    }
    sort(contatos.begin(), contatos.end(),
         [](auto a, auto b) { return a.getName() < b.getName(); });
  }

  void rmContact(std::string name) {
    int index = findContact(name);
    if (index == -1) {
      cout << "fail: contato inexistente" << endl;
    } else {
      std::vector<Contact> newContact;
      for (int i = 0; i < contatos.size(); i++) {
        if (i != index) {
          newContact.push_back(contatos[i]);
        }
      }
      contatos = newContact;
    }
  }

  Contact *getContact(std::string id) {
    int index = findContact(id);
    if (index == -1) {
      return nullptr;
    } else {
      return &contatos[index];
    }
  }

  std::vector<Contact> getContatos() { return contatos; }

  std::vector<Contact> search(std::string pattern) {
    vector<Contact> result;

    for (int i = 0; i < (int)contatos.size(); i++) {
      string aux = contatos[i].str();

      if (aux.find(pattern) != string::npos) {
        result.push_back(contatos[i]);
      }
    }

    return result;
  }

  std::vector<Contact> getFavorited() {
    vector<Contact> favs;

    for (int i = 0; i < (int)contatos.size(); i++) {
      if (contatos[i].isFavorited()) {
        favs.push_back(contatos[i]);
      }
    }

    return favs;
  }

  std::string str() {
    stringstream ss;

    for (int i = 0; i < (int)contatos.size(); i++) {
      ss << contatos[i].str() << (i == (int)(contatos.size() - 1) ? "" : "\n");
    }

    return ss.str();
  }
};

std::ostream &operator<<(std::ostream &out, Fone fone) {
  return out << fone.str();
}
std::ostream &operator<<(std::ostream &out, Contact contato) {
  return out << contato.str();
}
std::ostream &operator<<(std::ostream &out, Agenda agenda) {
  return out << agenda.str();
}

int main() {
  Agenda agenda;
  while (true) {
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line, ' ');
    if (args[0] == "end") {
      break;
    } else if (args[0] == "add") { // name id:fone id:fone ...
      std::vector<Fone> fones;
      for (int i = 2; i < (int)args.size(); i++) {
        auto parts = fn::split(args[i], ':');
        fones.push_back(Fone(parts[0], parts[1]));
      }
      agenda.addContato(args[1], fones);
    } else if (args[0] == "show") {
      fn::write(agenda);
    } else if (args[0] == "rmFone") { // id index
      Contact *contato = agenda.getContact(args[1]);
      if (contato != nullptr)
        contato->rmFone((int)+args[2]);
    } else if (args[0] == "rm") { // id
      agenda.rmContact(args[1]);
    } else if (args[0] == "tfav") { // id 1 ou 0
      Contact *contato = agenda.getContact(args[1]);
      if (contato != nullptr)
        contato->toogleFavorited();
    } else if (args[0] == "favs") {
      agenda.getFavorited() | fn::JOIN("\n") | fn::WRITE();
    } else if (args[0] == "search") { // pattern
      agenda.search(args[1]) | fn::JOIN("\n") | fn::WRITE();
    } else {
      fn::write("fail: comando invalido");
    }
  }
}
