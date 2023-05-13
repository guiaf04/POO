#include <fn.hpp>
#include <iostream>

using namespace fn;
using namespace std;

class Pet{
private:
    int energyMax, hungryMax, cleanMax;
    int energy {1};
    int hungry {1};
    int clean {1};
    int diamonds{0};
    int age{0}; // não tem set para diamantes e idade pois não tem limites
    bool alive{true};

    bool testAlive() {
        if(alive)
            return true;
        write("fail: pet esta morto");
        return false;
    }

public:
    void setHungry(int value) {
        if (value <= 0) {
            hungry = 0;
            write("fail: pet morreu de fome");
            alive = false;
        } else if (value > hungryMax) {
            hungry = hungryMax;
        } else {
            hungry = value;
        }
    }
    void setEnergy(int value) {
      if (value <= 0) {
            energy = 0;
            write("fail: pet morreu de fraqueza");
            alive = false;
        } else if (value > energyMax) {
            energy = energyMax;
        } else {
            energy = value;
        }
    }

    void setClean(int value) {
      if (value <= 0) {
            clean = 0;
            write("fail: pet morreu de sujeira");
            alive = false;
        } else if (value > cleanMax) {
            clean = cleanMax;
        } else {
            clean = value;
        }
    }

    Pet(int energy = 0, int hungry = 0, int clean = 0) {
      this->energyMax = energy;
      this->hungryMax = hungry;
      this->cleanMax = clean;
      
      this->setEnergy(energy);
      this->setHungry(hungry);
      this->setClean(clean);
    }

    void play() {
        if (!testAlive())
            return;
        setEnergy(getEnergy() - 2);
        setHungry(getHungry() - 1);
        setClean(getClean() - 3);
        diamonds += 1;
        age += 1;
    }

    void shower() {
      if(!testAlive()){
        return;
      }

      setEnergy(getEnergy() - 3);
      setHungry(getHungry() - 1);
      setClean(cleanMax);
      age += 2;
    }

    void eat() {
      if(!testAlive()){
        return;
      }
      setEnergy(getEnergy() - 1);
      setHungry(getHungry() + 4);
      setClean(getClean() - 2);
      age += 1;
    }

    void sleep() {
      if(!testAlive()){
        return;
      }

      if(getEnergy() > (energyMax - 5)){
        write("fail: nao esta com sono");
      }else{
        int turnos = energyMax - getEnergy();
        setEnergy(energyMax);
        setHungry(getHungry() - 1);
        age += turnos;
      }
    }


    int getClean() {
        return clean;
    }
    int getHungry() {
        return hungry;
    }
    int getEnergy() {
        return energy;
    }
    int getEnergyMax() {
        return energyMax;
    }
    int getCleanMax() {
        return cleanMax;
    }
    int getHungryMax() {
        return hungryMax;
    }

    string toString() {
        return format("E:{}/{}, S:{}/{}, L:{}/{}, D:{}, I:{}", energy, energyMax, hungry, hungryMax, clean, cleanMax, diamonds, age);
    }

};


int main() {
    Pet pet(1,1,1);
    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line, ' ');        

        if (args[0] == "end") {
            break;
        } else if (args[0] == "init") {
            pet = Pet(number(args[1]), number(args[2]), number(args[3]));
        } else if (args[0] == "show") {
            write(pet.toString());
        } else if (args[0] == "play") {
            pet.play();
        } else if (args[0] == "eat") {
            pet.eat();
        } else if (args[0] == "sleep") {
            pet.sleep();
        } else if (args[0] == "shower") {
            pet.shower();
        } else {
            write("fail: comando invalido");
        }
    }
}
