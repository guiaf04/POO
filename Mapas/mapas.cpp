#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
  map<string, string> contatos{};
  std::vector<string, string> fones = {"tim", "8124"}, {"vivo", "1034"};
  for (int i = 0; i < 10; i++) {
    map<string, string>();
  }

  for (auto [key, value] : contatos) {
    cout << key << ":" << value << endl;
  }
}