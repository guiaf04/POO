#include <algorithm>
#include <fn.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace fn;

bool in(std::vector<int> vet, int x) {
  for (auto elem : vet) {
    if (elem == x) {
      return true;
      break;
    }
  }
  return false;
}

int index_of(std::vector<int> vet, int x) {
  for (int i = 0; i < vet.size(); i++) {
    if (vet[i] == x) {
      return i;
      break;
    }
  }
  return -1;
}

int find_if(const std::vector<int> &vet) {
  for (int i = 0; i < vet.size(); i++) {
    if (vet[i] > 0) {
      return i;
      break;
    }
  }
  return -1;
}

int min_element(const std::vector<int> &vet) {
  if(vet.size() < 1){
    return -1;
  }
  
  int min = vet[0];
  int min_indice = 0;

  for (int i = 1; i < vet.size(); i++) {
    if (vet[i] < min) {
      min = vet[i];
      min_indice = i;
    }
  }

  return min_indice;
}

int find_min_if(const std::vector<int> &vet) {
  if(vet.size() < 1){
    return -1;
  }
  
  int min = vet[0];
  int min_indice = -1;//começa por -1 caso não haja nenhum homem, se houver o laço já atualiza

  for (int i = 1; i < vet.size(); i++) {
    if (vet[i] > 0 && vet[i] < min) {
      min = vet[i];
      min_indice = i;
    }
  }

  return min_indice;
}

int main() {

  auto STRTOVET = [](auto s) {
    return map(split(s.substr(1, s.size() - 2), ','), FNT(x, (int)+x));
  };

  while (true) {
    auto line = input();
    write("$" + line);
    auto args = split(line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "in") {
      write(tostr(in(STRTOVET(args[1]), +args[2])));
    } else if (args[0] == "index_of") {
      write(index_of(STRTOVET(args[1]), +args[2]));
    } else if (args[0] == "find_if") {
      write(find_if(STRTOVET(args[1])));
    } else if (args[0] == "min_element") {
      write(min_element(STRTOVET(args[1])));
    } else if (args[0] == "find_min_if") {
      write(find_min_if(STRTOVET(args[1])));
    } else {
      write("fail: unknown command");
    }
  }
}