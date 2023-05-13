//1.Fiz tudo sozinho e passou em todos os casos
//2.Utilizei apenas o Replit
//3.Levei em média 2 horas
//4.Aprendi sobre construtores

#include <aux.hpp>
#include <fn.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace fn;
using namespace std;

class Time {
private:
  int hour{0};
  int minute{0};
  int second{0};

public:
  void timer(int hour = 0, int minute = 0, int second = 0){// inicializando o construtor, colocando em 0 para ser parâmetro default, ou seja, não é necessário passá-los
    this->setHour(hour);
    this->setMinute(minute);
    this->setSecond(second);
  }

  bool setHour(int hora) {
    if (hora >= 0 && hora <= 23) {
      this->hour = hora;
      return true;
    }else{
      write("fail: hora invalida");
      return false;
    }
  }
  bool setMinute(int minute) {
    if(minute >= 0 && minute <= 59){
      this->minute = minute;
      return true;
    }else{
      write("fail: minuto invalido");
      return false;
    }
  }

  bool setSecond(int second) {
    if(second >= 0 && second <= 59){
      this->second = second;
      return true;  
    }
    else{
      write("fail: segundo invalido");
      return false;
    }
  }

  int getHour() {
    return hour;
  }

  int getMinute() {
    return minute; 
  }

  int getSecond() {
    return second;
  }

  void nextSecond() {
      if(second == 59){
        if(minute == 59){
          if(hour == 23){
            hour = 0;
            minute = 0;
            second = 0;
          }else{
            hour += 1;
            minute = 0;
            second = 0;
          }
        }else{
          second = 0;
          minute += 1;
        }
      }else{
        second += 1;
      }
  }

  string str() {
    return format("{%02d}:{%02d}:{%02d}", hour, minute, second);
  }
};

int main() {
  Time t;

  while (true) {
    string line = input();
    write("$" + line);

    vector<string> args = split(line, ' ');

    if (args[0] == "end") {
      break;
    } else if (args[0] == "show") {
      write(t.str());
    } else if (args[0] == "next") {
      t.nextSecond();
    } else if (args[0] == "init"){//revisar pois parece gambiarra
      if(!t.setHour(number(args[1]))){
        t.setHour(0);
      }
      if(!t.setMinute(number(args[2]))){
        t.setMinute(0);
      }
      if(!t.setSecond(number(args[3]))){
        t.setSecond(0); 
      }
    } else if(args[0] == "set"){
      t.timer(number(args[1]), number(args[2]), number(args[3]));
    } else{
      break;
    }
  }
}