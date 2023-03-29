#include <iostream>
#include <string>

using std::cout;
using std::endl;

struct Apa {
  Apa(int a) : _a(a) {}
  int _a;
};

struct Kaka {
  Kaka(Apa &apa) : _apa(apa) {}
  int _b;
  Apa &_apa;
};

struct Burk {
  Burk() : _kaka(_apa), _apa(*new Apa(42)) {}

  Kaka _kaka;
  Apa &_apa;
};

int main() {

  Burk burk;
  cout << "Krassle" << endl;
  cout << burk._kaka._apa._a;
}
