#include <iostream>
#include <string>

using std::cout;
using std::endl;

struct B { int ib; };

struct A { B &b; };

int main() {
  cout << "Hello world " << endl;
  B theb{42};
  A a1{theb};
  A a2{theb};

  a1 = a2;
}
