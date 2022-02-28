#include <assert.h>
#include <bitset>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

using std::cout;
using std::endl;

class A {
public:
  virtual bool foo() = 0;

  template <typename T> void assert_defined_here() {
    assert(typeid(this) == typeid(T));
  }
};

class B : public A {
public:
  virtual bool foo() override;
};

bool B::foo() {
  //  assert(typeid(this) == typeid(B));
  //  assert(typeid(this) == typeid(decltype(foo)));
  assert_defined_here<B>();
  return true;
}

class C : public B {
public:
};

int main() {
  B b;
  C c;
  b.foo();
  //  c.foo();
  bool (A::*pt)() = &A::foo;
  std::cout << "decltype(A::foo): "
            << std::is_member_function_pointer<decltype(pt)>::value
            << std::endl;
  {
    bool (B::*pt)() = &B::foo;
    std::cout << "decltype(B::foo): "
              << std::is_member_function_pointer<decltype(pt)>::value
              << std::endl;
  }
}
