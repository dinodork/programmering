#include <cstddef>
#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using std::cout;
using std::endl;

struct FooBase {
  void foo() { cout << "foo()" << endl; }
};
struct FieBase {
  void fie() { cout << "fie()" << endl; }
};

template <typename... Bases> class Derived : public Bases... {};

int main() {
  Derived<FooBase, FieBase> d;
  d.foo();
  d.fie();
}
