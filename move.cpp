#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

struct A {
  A() { cout << "Constructing an A" << endl; }
  A(const A &other) { cout << "Copy" << endl; }
  A(A &&other) noexcept { cout << "move" << endl; }
  ~A() { cout << "Cleaning up" << endl; }
  int member;
};

void foo(A a) { cout << "foo(A)" << endl; }
void fum(A &&a);
void fum(A &a);
void fie(A &&a) {
  cout << "fie(A&&)" << endl;
  fum(a);
}

void fum(A &&a) {
  cout << "fum(A&&)" << endl;
  a.member = 666;
}
void fum(A &a) {
  cout << "fum(A&)" << endl;
  a.member = 666;
}

int main() {
  cout << "With copy semantics:" << endl;
  {
    A a;
    foo(a);
  }
  cout << "With move semantics:" << endl;
  fie(A());

  cout << "With move semantics again:" << endl;
  A a;
  a.member = 42;
  fie(std::move(a));
  cout << "member:" << a.member << endl;
}
