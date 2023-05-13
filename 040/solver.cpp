//Fiz tudo sozinho no replit
//Levei em média 30 minutos
//Aprofundei os conhecimentos de fup em c++

#include <iostream>
#include <vector>

int count(std::vector<int> vet, int x) {
  int cont = 0;
  for(auto elem : vet){
    if(elem == x){
      cont++;
    }
  }
  return cont;
}

int sum(std::vector<int> vet) {
  int sum = 0;
  for(auto elem : vet){
    sum += abs(elem);
  }
  return sum;
}

double average(const std::vector<int> &vet) {
  double average = (sum(vet))/ (double) vet.size();
  return average;
}

std::string more_men(const std::vector<int> &vet) {
  int men = 0, women = 0;
  for (auto elem : vet){
    if(elem > 0){
      men++;
    }else{
      women++;
    }
  }

  if(men > women){
    return "men";
  }else if(men < women){
    return "women";
  }else{
    return "draw";
  }
}

std::string half_compare(const std::vector<int> &vet) {
  int first_half = 0, second_half = 0;
  
  for(unsigned int i = 0; i < vet.size(); i++){
    if(i <= ((vet.size() - 1)/2)){
      first_half += abs(vet[i]);
    }else{
      second_half += abs(vet[i]);
    }
  }

  if(first_half > second_half){
    return "first";
  }else if(first_half < second_half){
    return "second";
  }else{
    return "draw";
  }
}

std::string sex_battle(const std::vector<int> &vet) {
  int men = 0, women = 0;
  double average_men = 0, average_women = 0;
  
  for (auto elem : vet){
    if(elem > 0){
      men++;
      average_men += abs(elem);
    }else{
      women++;
      average_women += abs(elem);
    }  
  }
  
  average_men /= men;
  average_women /= women;
  
  if(average_men > average_women){
    return "men";
  }else if(average_men < average_women){
    return "women";
  }else{
    return "draw";
  }
}

#include <fn.hpp>
using namespace fn;

int main() {

  auto str2vet = [](auto s) {
    return s.substr(1, s.size() - 2) | SPLIT(',') | MAP(FNT(x, (int)+x));
  };

  while (true) {
    auto line = input();
    write("$" + line);
    auto args = split(line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "count") {
      count(str2vet(args[1]), +args[2]) | WRITE();
    } else if (args[0] == "sum") {
      sum(str2vet(args[1])) | WRITE();
    } else if (args[0] == "more_men") {
      more_men(str2vet(args[1])) | WRITE();
    } else if (args[0] == "half_compare") {
      half_compare(str2vet(args[1])) | WRITE();
    } else if (args[0] == "more_men_or_women") {
      more_men(str2vet(args[1])) | WRITE();
    } else if (args[0] == "sex_battle") {
      sex_battle(str2vet(args[1])) | WRITE();
    } else if (args[0] == "average") {
      average(str2vet(args[1])) | TOSTR("%.2f") | WRITE();
    } else {
      "fail: unknown command" | WRITE();
    }
  }
}
