//Fiz tudo sozinho pelo replit
//Passou em todos os casos de teste
//Demorei em média 4h
//Reforcei o conhecimento de mapas e exceções

#include <algorithm>
#include <fn.hpp>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace fn;
using namespace std;

class Pessoa {
  string name;
  bool meia;

public:
  Pessoa(string name = "", bool meia = true) {
    this->name = name;
    this->meia = meia;
  }

  string getName() { return name; }

  bool getMeia() { return meia; }

  string toString() { return name + (meia ? ":meia" : ":inteira"); }
};

class Setor {
  string event;
  string name;
  float price;

public:
  Setor(string event = "", string name = "", float price = 0) {
    this->event = event;
    this->name = name;
    this->price = price;
  }

  string getEvent() { return event; }

  string getName() { return name; }

  float getPrice() { return price; }

  string toString() {
    return name + ":" + fn::tostr(fn::format("{%.2f}", price));
  }
};

class Evento {
  string name;
  std::unordered_map<string, Setor> setores;

public:
  Evento(string name = "") { this->name = name; }

  string getName() { return name; }

  vector<Setor> getSetores() {
    vector<Setor> s;

    for (auto& p : setores) {
      s.push_back(p.second);
    }

    return s;
  }

  void addSetor(string name, float price) {
    if (setores.find(name) != setores.end())
      throw runtime_error("fail: setor ja existe");

    setores.insert(std::make_pair(name, Setor(this->name, name, price)));
  }

  Setor getSetor(string name) {
    if (setores.find(name) != setores.end()) {
      return setores[name];
    } else {
      throw runtime_error("fail: setor " + name + " nao existe");
    }
  }

  string toString() {
    stringstream ss;
    vector<Setor> s = getSetores();

    ss << name << " [";

    for(int i = (int) (s.size() - 1); i >= 0; i--){
      ss << s[i].toString();

      if (i != 0) {
        ss << ", ";
      }
    }

    ss << "]";

    return ss.str();
  }
};

class Venda {
  Pessoa pessoa;
  Setor setor;
  float valor;

public:

  Venda(Pessoa pessoa, Setor setor) {
    this->pessoa = pessoa;
    this->setor = setor;
    
    if(pessoa.getMeia() == true){
      this->valor = (setor.getPrice() / 2);
    }else{
      this->valor = setor.getPrice();
    }
  }

  Pessoa getPessoa() { return pessoa; }

  Setor getSetor() { return setor; }

  float getValor () { return valor; }

  string toString() {
    stringstream ss;
    ss << pessoa.getName() << ":" << setor.getEvent() << ":" << setor.getName() << ":" << fn::tostr(fn::format("{%.2f}", getValor()));
    return ss.str();
  }
};

class Bilheteria {
  vector<Venda> repVendas;
  std::map<string, Pessoa> repPessoas;
  std::map<string, Evento> repEventos;

public:
  Bilheteria() {}

  vector<Venda> getVendas() { return repVendas; }

  vector<Pessoa> getPessoas() {
    vector<Pessoa> pessoas;

    for (auto& p : repPessoas) {
      pessoas.push_back(p.second);
    }

    sort(pessoas.begin(), pessoas.end(),
         [](auto a, auto b) { return a.getName() < b.getName(); });

    return pessoas;
  }

  vector<Evento> getEventos() {
    vector<Evento> eventos;

    for (auto& p : repEventos) {
      eventos.push_back(p.second);
    }

    return eventos;
  }



  Pessoa getPessoa(string name){
    if(repPessoas.find(name) != repPessoas.end()){
      return repPessoas[name];
    } else {
      throw runtime_error("fail: pessoa " + name + " nao existe");
    }
  }

  Evento getEvento(string name){
    if(repEventos.find(name) != repEventos.end()){
      return repEventos[name];
    } else {
      throw runtime_error("fail: evento " + name + " nao existe");
    }
  }

  void addPessoa(string name, bool meia) {
    if (repPessoas.find(name) != repPessoas.end())
      throw runtime_error("fail: pessoa " + name + " ja existe");
    else {
      
      repPessoas.insert(std::make_pair(name, Pessoa(name, meia)));
    }
  }

  void addEvento(string name, int preco = 0) {
    if (repEventos.find(name) != repEventos.end())
      throw runtime_error("fail: evento " + name + " ja existe");
    else {
      repEventos.insert(std::make_pair(name, Evento(name)));
    }
  }

  void addSetor(string event_name, string setor_name, float preco) {
    repEventos[event_name].addSetor(setor_name, preco);
  }

  void vender(string person_name, string event_name, string setor_name){
    Pessoa p = getPessoa(person_name);
    Evento e = getEvento(event_name);
    Setor s = e.getSetor(setor_name);

    repVendas.push_back(Venda(p,s)); 
  }
};

int main() {

  Bilheteria b;
  while (true) {
    auto line = input();
    auto args = split(line, ' ');
    write("$" + line);

    try {
      if (args[0] == "end") {
        break;
      } else if (args[0] == "addPessoa") {
        b.addPessoa(args[1], (args[2] == "meia" ? true : false));
      } else if (args[0] == "pessoas") {
        vector<Pessoa> pessoas = b.getPessoas();
        stringstream ss;
        ss << "[";

        for (int i = 0; i < (int)pessoas.size(); i++) {
          ss << pessoas[i].toString();
          if (i < (int)pessoas.size() - 1)
            ss << ", ";
        }
        ss << "]";
        cout << ss.str() << endl;
      } else if (args[0] == "addEvento") {
        b.addEvento(args[1]);
      } else if (args[0] == "eventos") {
        vector<Evento> eventos = b.getEventos();

        for (auto& e : eventos) {
          cout << e.toString() << endl;
        }
      } else if (args[0] == "addSetor") {
        b.addSetor(args[1], args[2], stof(args[3]));
      }else if (args[0] == "vender"){
           b.vender(args[1], args[2], args[3]);
      }else if (args[0] == "vendas"){
           vector<Venda> v = b.getVendas();

           for(int i = 0; i <(int) v.size(); i++){
            cout << v[i].toString() << endl;
           }
      }else {
        write("fail: comando invalido");
      }
    } catch (exception &e) {
      write(e.what());
    }
  }
}
