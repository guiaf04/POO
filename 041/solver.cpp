#include <iostream>
#include "fn.hpp"
#include <algorithm>

using namespace std;

class Player {
private:
    int label;     // índice do player   
    int pos;       // posição dele no tabuleiro
    bool free;

public:
    Player(int label) { 
      this->label = label;
      pos = 0;
      free = true;
    }

    int getLabel() { return this->label; }

    int getPos() { return this->pos; }

    void setPos(int pos) { this->pos = pos; }

    void setFree(bool free) { this->free = free; }

    bool isFree() { return this->free; }

    std::string toString() {
        std::string status = (this->free ? "free" : "not free");
        return fn::format("Player {} at {} is {}", label, pos, status); 
    }
};

class Board {
private:
    std::vector<int> trapList; // posição das armadilhas
    bool running;   // se o jogo acabou
    int size;   // tamanho do tabuleiro
    std::vector<Player> players; // lista de jogadores

public:
    Board(int nPlayers, int size) { 
        this->size = size + 1;    
        running = true;
        
        for(int i = 0 ; i < nPlayers; i++){
            players.push_back(Player(i + 1));
        }

    }

    void addTrap(int pos) { trapList.push_back(pos); }

    void rollDice(int value) { 
      int nome = players[0].getLabel();
      int pos = players[0].getPos() + value;
      
      if(running == true){
        if(players.begin()->isFree() == false){
          if(value % 2 == 0){
            players.begin()->setFree(true);
            cout << "player" << to_string(nome) << " se libertou" << endl;
          }else{
            cout << "player" << to_string(nome) << " continua preso" << endl;
          }
        }else{

          if(players.begin()->getPos() + value >= size){
            cout << "player" << to_string(nome) << " ganhou" << endl;
            players.begin()->setPos(size - 1);

            Player p = players.front();
            players.push_back(p);
            players.erase(players.begin());

            running = false;
            
            return;
          }          
          
          cout << "player" << to_string(nome) << " andou para " << to_string(pos) << endl;
          
          for(int i = 0; i < trapList.size(); i++){
            if(players.begin()->getPos() + value == trapList[i]){
              cout << "player" << to_string(nome) << " caiu em uma armadilha" << endl;
              players.begin()->setPos(players.begin()->getPos() + value);
              players.begin()->setFree(false);

              Player p = players.front();
              players.push_back(p);
              players.erase(players.begin());

              return;
             }
          }

          
          players.begin()->setPos(players.begin()->getPos() + value);
        }

        Player p = players.front();
        players.push_back(p);
        players.erase(players.begin());
      }else{
        cout << "game is over" << endl;
      }
    }


    std::string toString() {
        std::stringstream ss;
        for (auto p : this->players) {
            auto line = std::string(this->size, '.');
            line[p.getPos()] = p.getLabel() + '0';
            ss << "player" << p.getLabel() << ": " << line << std::endl;
        }
        auto traps = std::string(this->size, '.');
        for (auto t : this->trapList)
            traps[t] = 'x';
        ss << "traps__: " << traps;
        return ss.str();
    }
};

int main() {
    Board board(0, 0);

    while(true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line);

        if      (args[0] == "end"    ) { break;                                 }
        else if (args[0] == "init"   ) { board = Board(+args[1], +args[2]);     }
        else if (args[0] == "addTrap") { board.addTrap(+args[1]);               }
        else if (args[0] == "roll"   ) { board.rollDice(+args[1]);              }
        else if (args[0] == "show"   ) { fn::write(board.toString());           }
        else                           { fn::write("fail: command not found");  }

    }
}