#include <iostream>
#include <string>
#include <unordered_set>

using std::cout;
using std::endl;

struct balle {
  std::string s_;
  balle(std::string s) : s_(s) {}
};

int main() {
  cout << "Hello world!" << endl;
  std::unordered_set<balle *> set;
  set.emplace(new balle("apa"));
}
