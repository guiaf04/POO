// 1. Fiz tudo e passou em todos os testes
// 2. Fiz sozinho
// 3. Levei em média de 3 horas
// 4. Aprendi a usar funções dentro do struct

#include <fn.hpp>
#include <iostream>
using namespace fn;
using namespace std;

struct Car {
  int pass{0}; // passageiros
  int passMax{2}; //máximo de passageiros
  int gas{0}; // gasolina
  int gasMax{100};//máximo de gasolina
  int km{0};//km andados

  void entrar() {
    if (pass == passMax) {
      write("fail: limite de pessoas atingido");
      return;
    }
    pass += 1;
  }

  string show() {
    return "pass: " + tostr(pass) + ", gas: " + tostr(gas) +
           ", km: " + tostr(km);
  }

  void leave() {
    if (pass == 0) {
      write("fail: nao ha ninguem no carro");
      return;
    }
    pass--;
  }

  void fuel(int qnt) {
    if ((qnt + gas) > gasMax) {
      gas = gasMax;
    } else
      gas += qnt;
  }

  void drive(int quilometragem) {
    if (pass == 0) {
      write("fail: nao ha ninguem no carro");
      return;
    } else if (gas == 0) {
      write("fail: tanque vazio");
    } else if (quilometragem > gas) {
      write("fail: tanque vazio apos andar " + tostr(gas) + " km");
      km += gas;
      gas = 0;
    } else {
      km += quilometragem;
      gas -= quilometragem;
    }
  }
};

int main() {
  Car car;

  while (true) {
    string line = input();
    write("$" + line);
    vector<string> args = split(line, ' ');

    if (args[0] == "end") {
      break;
    } else if (args[0] == "show") {
      write(car.show());
    } else if (args[0] == "enter") {
      car.entrar();
    } else if (args[0] == "leave") {
      car.leave();
    } else if (args[0] == "fuel") {
      car.fuel(number(args[1]));
    } else if (args[0] == "drive") {
      car.drive(number(args[1]));
    } else {
      break;
    }
  }
}
