#include <bitset>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using std::cout;
using std::endl;
using std::tuple;

class C {
  int x[4];

public:
  C() : x{0, 1, 2, 3} {}
};

void fie(int a, const char *b) { cout << "fie(int, cout char)" << endl; }

void fie(int a, int, const char *b) {
  cout << "fie(int, int, cout char)" << endl;
}

template <typename T, typename U> void foo(tuple<T, U> t) {
  fie(std::get<0>(t), std::get<1>(t));
}

template <typename... Args> void foo(Args... args) { fie(args...); }

int main() {
  cout << "hej" << endl;
  tuple<int, const char *> t(666, "hej");
  foo(t);

  foo(666, 42, "hej");
  holdem h(1, "apa");
}
