#include <fn.hpp>
#include <iomanip> //setprecision
#include <iostream>
#include <memory> //sharedptr
#include <sstream>
#include <utility> //exchange

class Lead {
  float thickness;
  std::string hardness;
  int size;

public:
  Lead(float thickness, std::string hardness, int size) {
    this->thickness = thickness;
    this->hardness = hardness;
    this->size = size;
  }

  int usagePerSheet() const {
    if (this->hardness == "HB")
      return 1;
    if (this->hardness == "2B")
      return 2;
    if (this->hardness == "4B")
      return 4;
    if (this->hardness == "6B")
      return 6;

    return 0;
  }

  float getThickness() const {
    return this->thickness; // todo
  }

  std::string getHardness() const {
    return this->hardness; // todo
  }

  int getSize() const {
    return this->size; // todo
  }

  void setSize(int size) { this->size = size; }
  std::string str() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << thickness << ":" << hardness
       << ":" << size;
    return ss.str();
  }
};

std::ostream &operator<<(std::ostream &ss, Lead gr) { return ss << gr.str(); }

struct Pencil {
  float thickness{0.f};
  std::shared_ptr<Lead> tip{nullptr};

  Pencil(float thickness = 0.0) { // todo thickness{thickness} {
    this->thickness = thickness;
  }

  bool hasGrafite() {
    return this->tip != nullptr; // todo
  }

  bool insert(std::shared_ptr<Lead> grafite) {
    if(hasGrafite()){
      fn::write("fail: ja existe grafite");
      return false;
    }
    
    if(grafite->getThickness() != this->thickness){
      fn::write("fail: calibre incompativel");
      return false;
    }

    this->tip = grafite;
    return true;
  }

  std::shared_ptr<Lead> remove() {
    if(hasGrafite()){
      std::shared_ptr<Lead> removed = this->tip;
      this->tip = nullptr;
      return removed;
    }
    return nullptr;
  }

  void writePage() {
    if(!hasGrafite()){
      fn::write("fail: nao existe grafite");
      return;
    }else if(tip->getSize() == 0 || tip->getSize() <= 10){
      fn::write("fail: tamanho insuficiente");
    }else if(tip->getSize() < tip->usagePerSheet()){
      fn::write("fail: folha incompleta");
      tip->setSize(0);
    }else if((tip->getSize() - tip->usagePerSheet()) < 10){
      fn::write("fail: folha incompleta");
      tip->setSize(10);
    }else{
      tip->setSize(tip->getSize() - tip->usagePerSheet());
    }
    
  }

  std::string str() {
    std::stringstream ss;
    ss << "calibre: " << thickness << ", grafite: ";
    if (tip != nullptr)
      ss << "[" << *tip << "]";
    else
      ss << "null";
    return ss.str();
  }
};

std::ostream &operator<<(std::ostream &os, Pencil l) { return os << l.str(); }

using namespace fn;

int main() {
  Pencil pencil;

  while (true) {
    auto line = input();
    write("$" + line);
    auto args = split(line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "show") {
      write(pencil);
    } else if (args[0] == "init") {
      pencil = Pencil(number(args[1]));
    } else if (args[0] == "insert") {
      pencil.insert(std::make_shared<Lead>(number(args[1]), args[2], (int)number(args[3])));
    } else if (args[0] == "remove") {
      pencil.remove();
    } else if (args[0] == "write") {
      pencil.writePage();
    }
  }
}
