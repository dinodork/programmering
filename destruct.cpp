#include <iostream>
#include <memory>

using std::cout;
using std::endl;

struct A {
  A() { cout << "A CTOR" << endl; }
  ~A() { cout << "A DTOR" << endl; }
};


struct Base {
  Base(A *a) {}
};

struct Descencent : public Base {
  Descencent() : Base(std::unique_ptr<A>(new A).get()) {}
};

int main() {

  Descencent descencent;

  std::cout << "hello " << std::endl;
}
