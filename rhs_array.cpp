#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

class Base {
public:
  virtual const char *foo() const = 0;
};

class A1 : public Base {
public:
  const char *foo() const { return "En A1"; }
};

class A2 : public Base {
public:
  const char *foo() const { return "En A2:a"; }
};

struct S {
  int i;
  Base &&base;

  //  S(const S & other) : i(other.i), base(std::move(other.base)) {}
};

A2 the_a2;

S arr[] = {{1, A1()}, {2, A2()}, {3, the_a2}};

int main() {
  for (S &s : arr)
    cout << "En arr: " << s.i << ", " << s.base.foo() << endl;
}
