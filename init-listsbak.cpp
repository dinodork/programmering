#include <iostream>

using std::cout;
using std::endl;

template <typename T> struct Component {
  explicit Component(T t) : _t(t) {}
  T _t;
};

class A {};

struct B {
  explicit B(A a) {}
};

class BBuilder {
public:
  BBuilder(Component<A> &a) : _a(a._t) {}
  B build() { return B(_a); }
  A _a;
};

class C {
public:
  C() : b(BBuilder(a).build()), a(A()) {}
  Component<B> b;
  Component<A> a;
};

int main() {
  cout << "hej" << endl;
  C c;
}
