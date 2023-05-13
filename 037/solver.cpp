// 1. Fiz tudo e passou em todos os testes.
// 2. Fiz sozinho.
// 3. Aprendi a usar e gerenciar listas.
// 4. Levei 2 horas.

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <fn.hpp>

class Pessoa {
    std::string nome;
public:
    Pessoa(std::string nome) { 
      this->nome = nome;
    }
    std::string getNome() const {
        return this->nome;
    }
    std::string str() const {
        return this->nome; // todo
    }
};
std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
    return (os << p.str());
}

class Mercantil {
    std::vector<std::shared_ptr<Pessoa>> caixas; //caixas do supermercado
    std::list  <std::shared_ptr<Pessoa>> esperando; //lista de clientes esperando

    bool validarIndice(int indice) {
        if(indice > (caixas.size() - 1) || indice < 0){
          return false;
        }else{ 
          return true;
        }
    }

public:
    Mercantil(int qtd_caixas) { 
      for(int i = 0; i < qtd_caixas; i++){
        this->caixas.push_back(nullptr);
      }
    }
    
    void chegar(const std::shared_ptr<Pessoa>& person) {
      this->esperando.push_back(person);
    }

    bool chamarNoCaixa(int indice) {
        if(validarIndice(indice)){
          if(this->caixas[indice] == nullptr){
            if(this->esperando.size() != 0){
              this->caixas[indice] = this->esperando.front();
              this->esperando.pop_front();
              return true;
            }else{
              fn::write("fail: sem clientes");
              return false;
            }
          }else{
            fn::write("fail: caixa ocupado");
            return false;
          }
        }else{
          return false;
        }
    }
    
    std::shared_ptr<Pessoa> finalizar(int indice) {
        std::shared_ptr<Pessoa> removed = nullptr;
        
        if(validarIndice(indice)){
          if(this->caixas[indice] != nullptr){
            removed = this->caixas[indice];
            this->caixas[indice] = nullptr;
          }else{
            fn::write("fail: caixa vazio");
          }
        }else{
          fn::write("fail: caixa inexistente");
        }

        return removed;
    }

    std::string str() const {
        auto caixas_str = caixas | fn::MAP(FNT(c, c == nullptr ? "-----" : c->getNome()));
        return "Caixas: " + fn::tostr(caixas_str) + "\n" + "Espera: " + fn::tostr(esperando);
    }
};

std::ostream& operator<<(std::ostream& os, const Mercantil& b) {
    return (os << b.str());
}

int main() {
    Mercantil bank(0);
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if      (args[0] == "end"   ) { break;                                          }
        else if (args[0] == "init"  ) { bank = Mercantil(+args[1]);                     }
        else if (args[0] == "call"  ) { bank.chamarNoCaixa(+args[1]);                   }
        else if (args[0] == "finish") { bank.finalizar(+args[1]);                       }
        else if (args[0] == "arrive") { bank.chegar(std::make_shared<Pessoa>(args[1])); }
        else if (args[0] == "show"  ) { fn::write(bank);                                }
        else                          { fn::write("fail: comando invalido");            }
        
    }
}

