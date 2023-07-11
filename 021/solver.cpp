#include <fn.hpp>
#include <iostream>
#include <map>

using namespace fn;
using namespace std;

class Discp;

class Aluno : public enable_shared_from_this<Aluno> {
  string id;
  std::map<string, shared_ptr<Discp>> discps;

public:
  Aluno(string id = "") { this->id = id; }

  string getId() { return id; }

  vector<shared_ptr<Discp>> getDiscps() {
    vector<shared_ptr<Discp>> p;
    for (auto &elem : discps) {
      p.push_back(elem.second);
    }

    return p;
  }

  string toStr();

  void addDiscp(shared_ptr<Discp> discp);

  void rmDiscp(string idDiscp);
};

class Discp {
  string id;
  std::map<string, shared_ptr<Aluno>> alunos;

public:
  Discp(string id = "") { this->id = id; }

  string getId() { return this->id; }

  vector<shared_ptr<Aluno>> getAlunos() {
    vector<shared_ptr<Aluno>> v;

    for (auto elem : alunos) {
      v.push_back(elem.second);
    }

    return v;
  }

  string toStr() {
    stringstream ss;
    vector<shared_ptr<Aluno>> a = getAlunos();
    ss << getId() << " [";

    for(unsigned int i = 0; i < a.size(); i++){
      ss << (i != 0 ? ", " : "") << a[i]->getId();
    }    
    ss << "]";
    return ss.str();
  }

  void addAluno(shared_ptr<Aluno> aluno) {
    if (alunos.find(aluno->getId()) != alunos.end()) {
      return;
    } else {
      alunos[aluno->getId()] = aluno;
      aluno->addDiscp(make_shared<Discp>(getId()));
    }
  }

  void rmAluno(string idAluno){
  auto it = alunos.find(idAluno);
  if(it == alunos.end())
    return;
  shared_ptr<Aluno> aluno = it->second;
  this->alunos.erase(it);
  aluno->rmDiscp(getId());
  }
};

void Aluno::addDiscp(shared_ptr<Discp> discp){
  if(discps.find(discp->getId()) != discps.end()){
    return;
  }

  discps[discp->getId()] = discp;
  discp->addAluno(shared_from_this());
}

void Aluno::rmDiscp(string idDiscp){
  auto it = discps.find(idDiscp);
  if(it == discps.end())
    return;
  shared_ptr<Discp> disciplina = it->second;
  this->discps.erase(it);
  disciplina->rmAluno(getId());
}

string Aluno::toStr(){
  stringstream ss;
    vector<shared_ptr<Discp>> v = getDiscps();
    ss << getId() << " [";

    for(unsigned int i = 0; i < v.size(); i++){
      ss << (i != 0 ? ", " : "") << v[i]->getId();
    }    
    ss << "]";
    return ss.str();
}

class Sistema {
  std::map<string, shared_ptr<Discp>> discps;
  std::map<string, shared_ptr<Aluno>> alunos;

public:
  Sistema(){
    
  }

  void addAluno(const string& idAluno){
    alunos[idAluno] = make_shared<Aluno>(idAluno);
  }

  void addDiscp(const string& idDiscp){
    discps[idDiscp] = make_shared<Discp>(idDiscp);
  }

  string toStr(){
    stringstream ss;
    ss << "- alunos\n";

    for(auto a : alunos){
      ss << a.second->toStr() << "\n";
    }

    ss << "- discps\n";

    for(auto d : discps){
      ss << d.second->toStr() << "\n";
    }

    return ss.str();
  }

  vector<shared_ptr<Aluno>> getAlunos(){
    vector<shared_ptr<Aluno>> a;

    for(auto elem : alunos){
      a.push_back(elem.second);
    }

    return a;  
  }

  vector<shared_ptr<Discp>> getDiscp(){
    vector<shared_ptr<Discp>> a;

    for(auto elem : discps){
      a.push_back(elem.second);
    }

    return a;  
  }

  void matricular(const string& idAluno, const string& idDiscp){
    if(alunos.find(idAluno) != alunos.end() && discps.find(idDiscp) != discps.end()){
      shared_ptr<Aluno> a = alunos[idAluno];
      shared_ptr<Discp> d = discps[idDiscp];
      //alunos[idAluno]->addDiscp(discps[idDiscp]);
      a->addDiscp(d);
    }
  }

  void desmatricular(const string& idAluno, const string& idDiscp){
    alunos[idAluno]->rmDiscp(idDiscp);
  }

  void removerAluno(string idAluno){
    for(auto elem : discps){
      elem.second->rmAluno(idAluno);
    }

    alunos.erase(idAluno);
  }

  void removerDisciplina(string idDiscp){
    for(auto elem : alunos){
      elem.second->rmDiscp(idDiscp);
    }

    discps.erase(idDiscp);
  }
};


int main() {

  Sistema s;
  while (true) {
    auto line = input();
    auto args = split(line, ' ');
    write("$" + line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "nwalu") {
      for (int i = 1; i < (int)args.size(); i++) {
        auto parts = fn::split(args[i], ':');
        s.addAluno(args[i]);
      }
    } else if (args[0] == "nwdis") {
      for (int i = 1; i < (int)args.size(); i++) {
        auto parts = fn::split(args[i], ':');
        s.addDiscp(args[i]);
      }
    } else if (args[0] == "show") {
      cout << s.toStr();
    } else if (args[0] == "tie") {
      for (int i = 2; i < (int)args.size(); i++) {
        auto parts = fn::split(args[i], ':');
        s.matricular(args[1], args[i]);
      }
    } else if (args[0] == "untie") {
        for (int i = 2; i < (int)args.size(); i++) {
        auto parts = fn::split(args[i], ':');
        s.desmatricular(args[1], args[i]);
      }
    } else if (args[0] == "rmalu") {
      s.removerAluno(args[1]);
    } else {
      write("fail: comando invalido");
    }
  }
}