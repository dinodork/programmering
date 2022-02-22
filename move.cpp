#include <iostream>
#include <string>

using std::cout;
using std::endl;

class A {
public:
  A() { cout << "A()" << endl; }
  A(const A &a) { cout << "A(const A&)" << endl; }
  A(A &&) { cout << "A(A&&)" << endl; }
  ~A() { cout << "~A()" << endl; }
};

class B {
public:
  B() { cout << "B()" << endl; }
  B(A a) : m_a(a) { cout << "B(A)" << endl; }
  B(A &&a) : m_a(a) { cout << "B(A&&)" << endl; }
  //  B(B &&) { cout << "B(&&)"; }

  ~B() { cout << "~B()" << endl; }
  A m_a;
};

class C {
public:
  C() { cout << "C()" << endl; }

  //  C(A &&a) : m_a((cout << "C{}" << endl, a)) { cout << "C(A&&)" << endl; }
  C(A &&a) : m_a((cout << "C{}" << endl, std::move(a))) {
    cout << "C(A&&)" << endl;
  }

  ~C() { cout << "~C()" << endl; }
  A m_a;
};

int main() {

  cout << "Move it !" << endl;
  {
    cout << "-- B --" << endl;
    A a;
    B b1(a);
  }
  {
    cout << "-- C --" << endl;
    A a;
    C c(std::move(a));
  }
}
