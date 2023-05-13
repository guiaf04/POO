#include <iostream>
#include <memory>
#include <sstream>
#include <fn.hpp>
using namespace fn;

class Person {
  std::string name; // atributo
  int age;

public:
  Person(std::string name = "", int age = 0) {
    this->name = name;
    this->age = age;
  }

  Person(int age) { // todo Person("", age) {
    this->age = age;
    this->name = "";
  }

  int getAge() {
    return this->age; // todo
  }
  std::string getName() {
    return this->name; // todo
  }
  std::string str() {
    std::stringstream ss;
    ss << name << ":" << age;
    return ss.str(); // todo
  }
};
std::ostream &operator<<(std::ostream &os, Person &p) { 
  return os << p.str(); 
}

class Motorcycle {
  std::shared_ptr<Person> person{nullptr}; // agregação
  int time{0};
  int power{1};

public:
  Motorcycle(int power = 1) { // todo power {power}
    this->power = power;
  }

  bool insertPerson(std::shared_ptr<Person> p) {
    if (this->person != nullptr) {
      write("fail: busy motorcycle");
      return false;
    }
    this->person = p;
    return true; // todo
  }

  std::string honk() {
    std::string aux = "";
    for(int i = 0; i < this->power; i++){
      aux += "e";
    }
    return "P" + aux + "m"; // todo
  }

  std::shared_ptr<Person> remove() {
    std::shared_ptr<Person> removed {nullptr};

    if (this->person != nullptr) {
      removed = this->person;
      this->person = nullptr;
    }else{
      write("fail: empty motorcycle");
      return nullptr;
    }
  
    return removed; // todo
  }

  void buyTime(int time) {
    this->time += time;
  }

  void drive(int time) {
    if(this->time == 0){
      write("fail: buy time first");
    }else if(this->person == nullptr){
      write("fail: empty motorcycle");
    }else if(person->getAge() > 10){
      write("fail: too old to drive");
    }else if(this->time < time){
      write("fail: time finished after " + tostr(time - this->time) + " minutes");
      this->time = 0;
    }else{
      this->time -= time;
    }
  }

  std::string str() {
    std::ostringstream os;
    os << "power:" << power << ", time:" << time;
    os << ", person:(" << (person == nullptr ? "empty" : person->str()) << ")";
    return os.str();
  }
};

std::ostream &operator<<(std::ostream &os, Motorcycle m) {
  return os << m.str();
}

int main() {
  Motorcycle m(1);

  while (true) {
    std::string line = input();
    auto args = split(line, ' ');
    write('$' + line);

    if (args[0] == "show") {
      write(m.str());
    } else if (args[0] == "leave") {
      auto person = m.remove();
      if (person != nullptr)
        write(person->str());
    } else if (args[0] == "honk") {
      write(m.honk());
    } else if (args[0] == "init") {
      m = Motorcycle(number(args[1]));
    } else if (args[0] == "enter") {
      m.insertPerson(std::make_shared<Person>(args[1], number(args[2])));
    } else if (args[0] == "buy") {
      m.buyTime(number(args[1]));
    } else if (args[0] == "drive") {
      m.drive(number(args[1]));
    } else if (args[0] == "end") {
      break;
    } else {
      write("fail: invalid command");
    }
  }
}
