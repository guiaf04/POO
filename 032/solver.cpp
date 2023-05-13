//1.Fiz tudo sozinho pelo replit
//2.Passou em todos os casos de teste
//3.Levei em média 1h
//4.Aprofundei os conceitos de fup em c++

#include <algorithm>
#include <fn.hpp>
#include <iostream>
#include <vector>

using namespace fn;

std::vector<int> get_men(std::vector<int> vet) {
  std::vector<int> men;

  if (vet.size() == 0) {
    return vet;
  }

  for (auto elem : vet) {
    if (elem > 0) {
      men.push_back(elem);
    }
  }

  return men;
}

std::vector<int> get_calm_women(std::vector<int> vet) {
  std::vector<int> women;

  for (auto elem : vet) {
    if (elem < 0) {
      if (abs(elem) < 10) {
        women.push_back(elem);
      }
    }
  }

  return women;
}

std::vector<int> sort(std::vector<int> vet) {
  if (vet.size() == 0) {
    return vet;
  }

  int aux, min, min_indice = 0;

  for (unsigned int i = 0; i < vet.size(); i++) {
    aux = vet[i];
    min = vet[i];
    min_indice = i;
    for (unsigned int j = i + 1; j < vet.size(); j++) {
      if (vet[j] < min) {
        min = vet[j];
        min_indice = j;
      }
    }
    vet[i] = min;
    vet[min_indice] = aux;
  }

  return vet;
}

std::vector<int> sort_stress(std::vector<int> vet) {
  if (vet.size() == 0) {
    return vet;
  }

  int aux, min, min_indice = 0;

  for (unsigned int i = 0; i < vet.size(); i++) {
    aux = vet[i];
    min = vet[i];
    min_indice = i;
    for (unsigned int j = i + 1; j < vet.size(); j++) {
      if (abs(vet[j]) < abs(min)) {
        min = vet[j];
        min_indice = j;
      }
    }
    vet[i] = min;
    vet[min_indice] = aux;
  }

  return vet;
}

std::vector<int> reverse(std::vector<int> vet) {
  std::vector<int> vet_reverse;
  if (vet.size() == 0) {
    vet_reverse = vet;
  }

  for (int i = vet.size() - 1; i >= 0; i--) {
    vet_reverse.push_back(vet[i]);
  }

  return vet_reverse;
}

std::vector<int> unique(std::vector<int> vet) {
  std::vector<int> vet_unique;

  for (unsigned int i = 0; i < vet.size(); i++) {
    int aux = vet[i], cont = 0;

    if(i == 0){
      vet_unique.push_back(vet[i]);
    }else{
      for(auto elem : vet_unique){
        if(aux == elem){
          cont++;
        }
      }

      if(cont == 0){
        vet_unique.push_back(vet[i]);
      }
    }
    
  }
  return vet_unique;
}

std::vector<int> repeated(std::vector<int> vet) {
  std::vector<int> vet_repeated;

  vet = sort(vet);
  
  for(int i = 0; i < vet.size(); i++){
    int cont = 0;
    for(int j = i + 1; j < vet.size(); j++){
      if (vet[i] == vet[j]){
        cont++;
      }
    }
    if(cont > 0){
      vet_repeated.push_back(vet[i]);
    }
  }
  
  return vet_repeated;
}

void reverse_inplace(std::vector<int> &vet) {
	if(vet.size() == 0){
	    return;
	}else{
	  for(unsigned int i = 0 , j = vet.size() - 1; i < j; i++, j--){
          int aux = vet[i];
    
          vet[i] = vet[j];
          vet[j] = aux;
        }
	}
}

int main() {
  auto strToVet = [](auto s) {
    return map(split(s.substr(1, s.size() - 2), ','), FNT(x, (int)+x));
  };

  while (true) {
    std::string line = input();
    auto args = split(line, ' ');
    write('$' + line);

    if (args[0] == "get_men") {
      write(get_men(strToVet(args[1])));
    } else if (args[0] == "get_calm_women") {
      write(get_calm_women(strToVet(args[1])));
    } else if (args[0] == "sort") {
      write(sort(strToVet(args[1])));
    } else if (args[0] == "sort_stress") {
      write(sort_stress(strToVet(args[1])));
    } else if (args[0] == "reverse") {
      write(reverse(strToVet(args[1])));
    } else if (args[0] == "unique") {
      write(unique(strToVet(args[1])));
    } else if (args[0] == "repeated") {
        write(repeated(strToVet(args[1])));
    } else if(args[0] == "reverse_inplace") { 
        auto vet = strToVet(args[1]);
        reverse_inplace(vet);
        write(vet);
    } else if (args[0] == "end") {
      break;
    }
  }
}
