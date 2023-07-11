//Fiz tudo sozinho, mas pesquisei na internt funções para ajudar a resolver
//Passou em todos os casos de teste
//Reforcei o conhecimento de herança
//Levei em média 3 horas e meia

#include <fn.hpp>
#include <iostream>

using namespace std;

class Valuable {
public:
  virtual std::string getLabel() const = 0;
  virtual double getValue() const = 0;
  virtual int getVolume() const = 0;
  virtual std::string str() const = 0;
  virtual ~Valuable() {}
};

std::ostream &operator<<(std::ostream &os, const Valuable &valuable) {
  return os << valuable.str();
}

class Coin : public Valuable {
  Coin(const std::string &label, double value, int volume)
      : label(label), value(value), volume(volume) {}

public:
  static const Coin C10;
  static const Coin C25;
  static const Coin C50;
  static const Coin C100;

  std::string getLabel() const override { return label; }

  int getVolume() const override { return volume; }

  double getValue() const override { return value; }

  std::string str() const override {
    return fn::format("{}:{%.2f}:{}", label, value, volume);
  }

private:
  std::string label;
  double value;
  int volume;
};

const Coin Coin::C10{"M10", 0.10, 1};
const Coin Coin::C25{"M25", 0.25, 2};
const Coin Coin::C50{"M50", 0.50, 3};
const Coin Coin::C100{"M100", 1.00, 4};

class Item : public Valuable {
  std::string label;
  double value;
  int volume;

public:
  Item(const std::string &label, double value, int volume) {
    this->label = label;
    this->value = value;
    this->volume = volume;
  }

  std::string getLabel() const override { return this->label; }

  int getVolume() const override { return this->volume; }

  double getValue() const override{
    return this->value; 
  }

  std::string str() const override {
    return fn::format("{}:{%.2f}:{}", label, value, volume);
  }

};

class Pig {
  int volumeMax;
  bool broken;
  std::vector<std::shared_ptr<Valuable>> valuables;

public:
  Pig(int volumeMax) { this->volumeMax = volumeMax; }

  void addValuable(const std::shared_ptr<Valuable> &val) {
    if(!isBroken()){
      if(getVolume() + val->getVolume() <= volumeMax)
        valuables.push_back(val);
      else
        cout << "fail: the pig is full" << endl;
    }else{
      cout << "fail: the pig is broken"<<endl;
    }
  }

  bool isBroken(){
    return broken;
  }

  void breakPig() {
    broken = true;
    
  }

  std::vector<std::shared_ptr<Coin>> extractCoins() { 
    vector<std::shared_ptr<Coin>> coins;

    for (auto it = valuables.begin(); it != valuables.end(); ++it) {
        if (std::shared_ptr<Coin> coin = std::dynamic_pointer_cast<Coin>(*it)) {
            coins.push_back(coin);
            valuables.erase(it);
            --it;  // Volta o iterador para o elemento anterior após a remoção
        }
    }

    return coins;
  }

  std::vector<std::shared_ptr<Item>> extractItems() { 
    vector<std::shared_ptr<Item>> itens;

    for (auto it = valuables.begin(); it != valuables.end(); ++it) {
        if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(*it)) {
            itens.push_back(item);
            valuables.erase(it);
            --it;  // Volta o iterador para o elemento anterior após a remoção
        }
    }

    return itens;
    
  }

  int getVolume() const { 
    int volume = 0;
    for(auto elem : valuables){
      volume += elem->getVolume();
    }

    return volume;
  }

  double getValue() const { 
    double value = 0;

    for(auto elem : valuables){
      value += elem->getValue();
    }

    return value;
  }

  std::string str() const {
      std::stringstream ss;

      ss << "[";

      for(int i = 0; i < valuables.size(); i++){
          ss << (i != 0 ? ", " : "") << valuables[i]->str();
      }

      ss << "] ";

      ss << ": " << fn::tostr(getValue(), "%.2f") << "$ : " << (broken ? "0" : std::to_string(getVolume())) << "/" << std::to_string(volumeMax) << " : " << (broken ? "broken" : "intact");

      return ss.str();
  }

};

  std::ostream &operator<<(std::ostream &os, const Pig &pig) {
    return os << pig.str();
  }

int main() {
    Pig pig(0);
    while (true) {
      try {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if (args[0] == "end") {
          break;
        } else if (args[0] == "init") {
          pig = Pig(+args[1]);
        } else if (args[0] == "addCoin") {
          switch ((int)+args[1]) {
          case 10:
            pig.addValuable(std::make_shared<Coin>(Coin::C10));
            break;
          case 25:
            pig.addValuable(std::make_shared<Coin>(Coin::C25));
            break;
          case 50:
            pig.addValuable(std::make_shared<Coin>(Coin::C50));
            break;
          case 100:
            pig.addValuable(std::make_shared<Coin>(Coin::C100));
            break;
          }
        } else if (args[0] == "addItem") {
          pig.addValuable(
              std::make_shared<Item>(args[1], +args[2], (int)+args[3]));
        } else if (args[0] == "break") {
          pig.breakPig();
        } else if (args[0] == "extractCoins") {
          if(!pig.isBroken())
            cout << "fail: you must break the pig first" << endl;
          else
            fn::write(pig.extractCoins());
        } else if (args[0] == "extractItems") {
          if(!pig.isBroken())
            cout << "fail: you must break the pig first" << endl;
          else
            fn::write(pig.extractItems());
        } else if (args[0] == "show") {
          fn::write(pig);
        } else {
          fn::write("fail: invalid command");
        }
      } catch (std::string s) {
        fn::write(s);
      }
    }
  }
