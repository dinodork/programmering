#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;
using std::string;

struct Apa {
  Apa(int a) : _a(a) {}
  int _a;
};

struct Apa_deleter {};

int main() {

  auto apan = std::make_shared<Apa>(42);
  std::shared_ptr<Apa> bepan(nullptr, [](Apa *apa) {
    cout << "diliit" << endl;
    delete apa;
  });
  //  bepan = apan;
  cout << apan->_a << endl;
  cout << "Hej hej " << endl;
}
