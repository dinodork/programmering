#include <iostream>
#include <functional>

using std::cout;
using std::endl;


int plusone(int x) { return x + 1; }

int foo(int a, std::function<int(int)> f) {
  return f(a);
}

class A { public: ~A() = default; };

int main() {
  A a;
  cout << "plusone(5) = " << foo(5, plusone) << endl;
  cout << "plusone(5) = " << foo(5, [](int x){ return x+1;} ) << endl;
  int one = 1;
  int two = 2;
  cout << "plusone(5) = " << foo(5, [one](int x){ return x+one;} ) << endl;
  cout << "plusone(5) = " << foo(5, [&](int x){ return x + one + two;} ) << endl;
}
