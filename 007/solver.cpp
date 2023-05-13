//Fiz tudo sozinho, mas como ajuda do monitor no tostr no Operador
//Levei em média 3h
//Aprendi a manipular enumerações e vetores
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fn.hpp>

using namespace std;

enum class Label{Deposit, Fee, Opening, Reverse, Withdraw};

string label_to_str(Label label){
  if(label == Label::Deposit){
      return "deposit";
    }else if(label == Label::Opening){
      return "opening";
    }else if(label == Label::Withdraw){
      return "withdraw";
    }else if(label == Label::Fee){
      return "fee";
    }else if(label == Label::Reverse){
      return "reverse";
    }else{
      return ""; 
    }
}

class Operation{
  int index;
  Label label;
  int value;
  int balance;

  public:

  Operation (int index = 0, Label label = Label::Opening, int value = 0, int balance = 0){
    this->index = index;
    this->label = label;
    this->value = value;
    this->balance = balance;
  }

  string toStr(){
    return fn::tostr(index, "%2d") + ": " + fn::tostr(label_to_str(label), "%8s") + ": " + fn::tostr(this->value, "%4d") + ": " + fn::tostr(this->balance, "%4d");
  }

  int getBalance(){
    return this->balance;
  }

  int getIndex(){
    return this->index;
  }

  Label getLabel(){
    return this->label;
  }

  int getValue(){
    return this->value;
  }
};

class BalanceManager{
  int balance;
  vector<Operation> extract;
  int nextId;

  public:

  BalanceManager(){
    this->balance = 0;
    this->nextId = 0;
  }

  void addOperation(Label label, int value){
    this->balance += value;
    Operation aux (nextId, label, value, this->balance);
    this->nextId++;
    this->extract.push_back(aux);
  }

  string tostr(){
      return "account: " + to_string(nextId) + "balance: " + to_string(balance); 
  }

  int getBalance(){
    return this->balance;
  }

  vector<Operation> getExtract(int qtdOp){
    if(qtdOp == 0){
      return this->extract;
    }else{
      vector<Operation> aux;
      for(int i = extract.size() - qtdOp; i < extract.size(); i++){
        aux.push_back(this->extract[i]);
      }
      
      return aux;
    }
  }

  Operation getOperation(int index){
    return extract[index];
  }
};


class Account{
  BalanceManager balanceManager;
  int id;

  public:

  Account(int id = 0){
    this->id = id;
    this->balanceManager.addOperation(Label::Opening, 0);
  }

  void deposit(int value){
    if(value < 0){
      cout << "fail: invalid value" << endl;
      return;
    }
    this->balanceManager.addOperation(Label::Deposit, value);
  }

  void fee(int value){
    this->balanceManager.addOperation(Label::Fee, -value);
  }

  void reverse(int index){
    if(index < 0 || index > this->balanceManager.getExtract(0).size()){
      cout << "fail: index " << index << " invalid" << endl;
    }else if(this->balanceManager.getOperation(index).getLabel() != Label::Fee){
      cout << "fail: index " << index << " is not a fee" << endl;
    }else{
      this->balanceManager.addOperation(Label::Reverse, - this->balanceManager.getOperation(index).getValue());
    }
  }

  void withdraw(int value){
    if(value > this->balanceManager.getBalance()){
      cout << "fail: insufficient balance" <<endl;
      return;
    }
    this->balanceManager.addOperation(Label::Withdraw, -value);
  }

  string toString(){
    return "account:" + to_string(this->id) + " balance:" + to_string(this->balanceManager.getBalance());
  }

  BalanceManager getBalanceManager(){
    return this->balanceManager;
  }
};


int main(){

  Account account;

  while(true){
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line);

    if (args[0] == "end") {
      break;
    }else if (args[0] == "init") {
      account = Account(+args[1]);
    }else if (args[0] == "show") {
      cout << account.toString() << endl;
    }else if(args[0] == "deposit"){
      account.deposit(+args[1]);
    }else if(args[0] == "withdraw"){
      account.withdraw(+args[1]);
    }else if(args[0] == "fee"){
      account.fee(+args[1]);
    }else if(args[0] == "extract"){
     vector<Operation> novo = account.getBalanceManager().getExtract(+args[1]); 
     for(int i = 0; i < novo.size(); i++){
       cout << novo[i].toStr() << endl;
     }
    }else if(args[0] == "reverse"){
      for(int i = 1; i < (int) args.size(); i++){
        account.reverse(+args[i]);
      }
    }else{
      cout << "fail: invalid command" << endl;
    }
  }
}
