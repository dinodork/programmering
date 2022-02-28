#include <cstddef>
#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using std::cout;
using std::endl;

struct Kalle {
  int a, b, c, d, e, f;
  void print() {
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    cout << "e = " << e << endl;
    cout << "f = " << f << endl;
  }
};

void foo() {
  int d = 4;
  int e = 5;
  int f = 6;
  cout << "foo" << endl;
}

int main() {
  int a = 1;
  int b = 2;
  int c = 3;
  auto k = new (&a) Kalle;
  k->print();
  int d = 42;
  k->print();
  foo();
  k->print();
}
