//Fiz tudo sozinho
//Passou em todos os casos
//Levei em média 1 hora e meia
//Aprendi a usar enumeração
#include <fn.hpp>
#include <utility>
#include <iostream>

using namespace std;

class Coin {
  float value;
  int volume;
  string label;

  Coin(double value, int volume, string label)
      : value(value), volume(volume), label(label) {}

public:
  const static Coin C10;
  const static Coin C25;
  const static Coin C50;
  const static Coin C100;

  float getValue() const { return this->value; }
  int getVolume() const { return this->volume; }
  string getLabel() const { return this->label; }

  string tostr() {
    return "value: " + to_string(this->value) +
           "volume: " + to_string(this->volume) + "label: " + this->label;
  }
};

const Coin Coin::C10{0.10, 1, "C10"};   // como o construtor é
const Coin Coin::C25{0.25, 2, "C25"};   // um método privado, então
const Coin Coin::C50{0.50, 3, "C50"};   // ao fazer isso, só essas
const Coin Coin::C100{1.00, 4, "C100"}; // moedas são válidas,
                                        // fazendo um enumeração.

class Item {
  string label;
  int volume;

public:
  Item(string label, int volume) {
    this->label = label;
    this->volume = volume;
  }

  int getVolume() const {
    return this->volume;
  }

  string getLabel() const {
    return this->label;
  }

  void setVolume(int volume) { 
      this->volume = volume; 
  
}
  void setLabel(string label) { 
      this->label = label; 
  }

  string str() const {
    return "volume: " + to_string(this->volume) + "label: " + this->label;
  }
};

ostream &operator<<(ostream &os, const Item &item) {
  return os << item.str();
}

class Pig {
  std::vector<std::string> itens;
  double value{0};
  int volume{0};
  int volumeMax{0};
  bool broken{false};

public:
  Pig(int volumeMax = 0) { // todo
    this->volumeMax = volumeMax;
  }

  bool addCoin(Coin coin) {
    if(isBroken()){
      fn::write("fail: the pig is broken");
      return false;
    }
    if(this->volume + coin.getVolume() > this->volumeMax){
      fn::write("fail: the pig is full");
      return false;
    }else{
      this->volume += coin.getVolume();
      this->value += coin.getValue();
      return true;
    }
  
  }

  bool addItem(Item item) {
    if(isBroken()){
      fn::write("fail: the pig is broken");
      return false;
    }

    if(this->volume + item.getVolume() > this->volumeMax){
      fn::write("fail: the pig is full");
      return false;
    }else{
      this->volume += item.getVolume();
      this->itens.push_back(item.getLabel());
      return true;
    }
  }

  bool breakPig() {
    this->broken = true;
    this->volume = 0;
    return true;
  }

  double getCoins() {
    if(isBroken()){
      auto value = this->value;
      this->value = 0;
      return value;
    }else{
      fn::write("fail: you must break the pig first");
      return 0;roken
    }
  }

  std::string getItems() {
    if(isBroken()){
      string aux = "[";
      for(auto i = 0; i < this->itens.size(); i++){
          if(i == 0){
            aux += itens[i];
          }else if(i < (this->itens.size() - 1)){
            aux += ", ";
            aux += itens[i];
          }else{
            aux += ", ";
            aux += itens[i];
          }
      }
      aux += "]";
      this->itens.clear();
      this->itens.push_back("");
      return aux;
    }else{
      fn::write("fail: you must break the pig first");
      return "[]";
    }
  }

  int getVolume(){
    return this->volume;
  }

  int getVolumeMax(){
    return this->volumeMax;
  }

  bool isBroken(){
    return this->broken;
  }roken

  std::string str() const {
    string aux = "[";
    for(auto i = 0; i < this->itens.size(); i++){
        if(i == 0){
          aux += itens[i];
        }else {
          aux += ", ";
          aux += itens[i];
        }
    }
    string estado = this->broken ? "broken" : "unbroken";
    
    return aux + "] : " + fn::tostr(this->value, "%.2f") + "$ : " + to_string(this->volume)+ "/" 
               + to_string(this->volumeMax) + " : " + estado;
  }
};

std::ostream &operator<<(std::ostream &os, const Pig &pig) {
  return os << pig.str();
}

int main() {

  Pig pig;
  while (true) {
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "addCoin") {
      if (args[1] == "10")
        pig.addCoin(Coin::C10);
      else if (args[1] == "25")
        pig.addCoin(Coin::C25);
      else if (args[1] == "50")
        pig.addCoin(Coin::C50);
      else if (args[1] == "100")
        pig.addCoin(Coin::C100);
    } else if (args[0] == "init") {
      pig = Pig((int)+(args[1]));
    } else if (args[0] == "addItem") {
      pig.addItem(Item(args[1], (int)+(args[2])));
    } else if (args[0] == "break") {
      pig.breakPig();
    } else if (args[0] == "getCoins") {
      fn::write(fn::tostr(pig.getCoins(), "%.2f"));
    } else if (args[0] == "getItems") {
      fn::write(pig.getItems());
    } else if (args[0] == "show") {
      fn::write(pig);
    } else {
      fn::write("fail: invalid command");
    }
  }
}
