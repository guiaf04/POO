#include <iostream>
#include <ostream>
#include <vector>
#include <sstream>

using namespace std;

class Player{
  int label;
  int pos;
  bool free;

  public:

  Player(int label = 0){
    this->label = label;
    this->free = true;
    this->pos = 0;
  }

  bool isfree(){
    return this->free;
  }

  string tostr(){
    return "pos: " + to_string(this->pos) + "label: " + to_string(this->label); 
  }

  int getLabel(){
    return this->label;
  }

  int getPos(){
    return this->pos;
  }

  void setPos(int pos){
    this->pos = pos;
  }

  void setFree(int free){
    this->free = free;
  }
};

class Board{
  vector<int> traplist;
  vector<Player> players;
  bool running;
  int boardsize;

  public:

  Board(int nPlayers, int boadsize){
    this->boardsize = boadsize + 1;

    for (int i = 1; i <= nPlayers; i++) {
      this->players.push_back(Player(i));
    }
  }

  string tostr(){
    auto str = ""; 
  }
  
};