#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
#include <iomanip> //setprecision
#include <fn.hpp>
using namespace fn;

class Grafite{
    float calibre;
    std::string dureza;
    int tamanho;
public:
    Grafite(float calibre, std::string dureza, int tamanho) {
        this->calibre = calibre;
        this->dureza = dureza;
        this->tamanho = tamanho;
    }
    int desgastePorFolha() {
        if (dureza == "HB")
            return 1;
        if (dureza == "2B")
            return 2;
        if (dureza == "4B")
            return 4;
        return 6;
    }
    float getCalibre() {
        return calibre;
    }
    std::string getDureza() {
        return dureza;
    }
    int getTamanho() {
        return tamanho;
    }
    void setTamanho(int tamanho) {
        this->tamanho = tamanho;
    }
    std::string str() const {
        std::ostringstream os;
        os << std::fixed << std::setprecision(1) << calibre << ":" << dureza << ":" << tamanho;
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, Grafite g) {
    return os << g.str();
}

using PGrafite = std::shared_ptr<Grafite>;

struct Lapiseira{
    float calibre {0.f};
    PGrafite grafite {nullptr};
    std::list<PGrafite> tambor;

    Lapiseira(float calibre = 0.0) { 
      this->calibre = calibre;
    }

    bool inserir(PGrafite grafite) {
      if(grafite->getCalibre() != this->calibre){
        fn::write("fail: calibre incompatível");
        return false;
      }
      
      this->tambor.push_back(grafite);
      return true;
    }

    PGrafite remover() {
      if(*tambor.begin() == nullptr){
        fn::write("fail: nao tem grafite");
        return nullptr;
      }

      PGrafite removed = this->grafite;
      this->grafite = nullptr;

      return removed;
    }

    void write() {
      if(this->grafite == nullptr){
        fn::write("fail: nao existe grafite no bico");
        return;  
      }else if(grafite->getTamanho() <= 10){
        fn::write("fail: tamanho insuficiente");
        return;
      }else if(grafite->getTamanho() < grafite->desgastePorFolha()){
        fn::write("fail: folha incompleta");
        grafite->setTamanho(0);
        return;
      }else if((grafite->getTamanho() - grafite->desgastePorFolha()) < 10){
        fn::write("fail: folha incompleta");
        grafite->setTamanho(10);
        return;
      }else{
        grafite->setTamanho(grafite->getTamanho() - grafite->desgastePorFolha());
      }
    } 

    void puxar() {
      if(this->grafite != nullptr){
        fn::write("fail: ja existe grafite no bico");
        return;
      }
      
      this->grafite = this->tambor.front();
      this->tambor.pop_front();
    }
    std::string str() const {
        auto fngr = [](PGrafite g) { return "[" + (g == nullptr ? "" : g->str()) + "]"; };
        std::ostringstream os;
        os << "calibre: " << calibre 
           << ", bico: " << fngr(grafite)
           << ", tambor: {" << (tambor | MAP(fngr) | JOIN("")) << "}";
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Lapiseira& l) {
    return os << l.str();
}

int main() {
    Lapiseira lapiseira;
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "show") {
            fn::write(lapiseira.str());
        } else if (args[0] == "init") {
            lapiseira = Lapiseira((float) +args[1]);
        } else if (args[0] == "insert") {
            lapiseira.inserir(std::make_shared<Grafite>((float) +args[1], args[2], +args[3]));
        } else if (args[0] == "remove") {
            lapiseira.remover();
        } else if (args[0] == "pull") {
            lapiseira.puxar();
        } else if (args[0] == "write") {
            lapiseira.write();
        } else {
            fn::write("fail: comando invalido");
        }
    }
}
