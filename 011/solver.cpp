#include <iostream>
#include <fn.hpp>
#include <iomanip>

using namespace std;

class Slot {
  string name;
  float price;
  int quantity;

public:

  Slot(string name = "", int quantity = 0, float price = 0){
    this->name = name;
    this->price = price;
    this->quantity = quantity;
  }
  
  string getName(){
    return this->name;
  }

  float getPrice(){
    return this->price;
  }

  int getQuantity(){
    return this->quantity;
  }

  void setName(string name){
    this->name = name;
  }

  void setPrice(float price){
    this->price = price;
  }

  void setQuantity(int quantity){
    this->quantity = quantity;
  }

  string toString(){
    return " [ " + fn::tostr(this->name, "%7s") +
        " : " + to_string(this->quantity) + " U : " + fn::tostr(this->price, "%.2f") + " RS]";
  }
};

class VendingMachine {
  vector<Slot> slots;
  float profit{0};
  float cash{0};
  int capacity{0};

public:

  VendingMachine(int capacity = 0){
    this->capacity = capacity;
    
    for(int i = 0; i < capacity; i++){
      slots.push_back(Slot("empty", 0, 0));
    }
  }
  
  Slot getSlot(int index){
    if(index < 0 || index > this->slots.size()){
      return Slot(nullptr); 
    }
    return slots[index];
  }

  void setSlot(int index, Slot slot){
    if(index < 0 || index > this->slots.size()){
      cout << "fail: indice nao existe" << endl;
    }else{
      this->slots[index] = slot;
    }
     
  }

  void clearSlot(int index){
    this->slots[index] = Slot("empty", 0, 0);
  }

  void insertCash(float cash){
    this->cash += cash;
  }

  float withdrawCash(){
    float aux = this->cash;
    this->cash = 0;
    return aux;
  }

  float getCash(){
    auto aux = this->cash;
    this->cash = 0;
    return aux;
  }

  float getProfit(){
    return this->profit;
  }

  void buyItem(int index){
    if(index < 0 || index > this->slots.size()){
      cout << "fail: indice nao existe" << endl;
    }else{
      if(cash >= slots[index].getPrice()){
        if(slots[index].getQuantity() > 0){
          cash -= slots[index].getPrice();
          slots[index].setQuantity(slots[index].getQuantity() - 1);
          profit += cash;
          cout << "voce comprou um " << slots[index].getName() << endl;
        }else{
          cout << "fail: espiral sem produtos" << endl;
        }
      }else{
        cout << "fail: saldo insuficiente" << endl;
      }
    }
  }

  string toString(){
    string aux = "saldo: ";
    aux = aux + fn::tostr(this->cash, "%.2f") + "\n";

    for(int i = 0; i < this->slots.size(); i++){
      aux = aux + to_string(i) + slots[i].toString() + "\n";
    }

    return aux;
  }
};


int main() {
  VendingMachine vendingMachine;
  while (true) {
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line);

    if (args[0] == "end") {
      break;
    }else if (args[0] == "init") {
      vendingMachine = VendingMachine(+args[1]);
    }else if (args[0] == "show") {
      cout << vendingMachine.toString();
    }else if (args[0] == "set") {
      Slot aux(args[2], (float) +args[3], +args[4]);
      vendingMachine.setSlot(+args[1], aux);
    }else if (args[0] == "limpar") {
      vendingMachine.clearSlot(+args[1]);
    }else if (args[0] == "dinheiro") {
      vendingMachine.insertCash((float) +args[1]);
    }else if (args[0] == "troco") {
      cout << "voce recebeu " << fixed <<setprecision(2) << vendingMachine.withdrawCash() << " RS" << endl;
    }else if (args[0] == "comprar") {
      vendingMachine.buyItem(+args[1]);
    }else{
      fn::write("fail: comando invalido");
    }
  }
}
