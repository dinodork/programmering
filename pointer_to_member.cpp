#include <functional>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

union Apa {
  int a;
  const char *b;
  char c;
};

template <typename T, T Apa::*Member> void manipulate(Apa *apa, T x) {
  apa->*Member = x;
}

void print(const Apa &apa) {
  cout << apa.a << ", " << apa.b << ", " << apa.c << endl;
}

int main() {
  Apa apa{1};
  //  print(apa);
  manipulate<int, &Apa::a>(&apa, 42);
  cout << apa.a << endl;
  manipulate<char, &Apa::c>(&apa, 'x');
  cout << apa.c << endl;
  manipulate<&Apa::c>(&apa, 'x');
  cout << apa.c << endl;
}
