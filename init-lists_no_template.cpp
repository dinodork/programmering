#include <bitset>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;

struct A {
  A() : x(42) {}
  int x;
};

struct B {
  explicit B(A *a) : y(a->x) {}
  int y;
};

class C {
public:
  C() : b(&a), a(A()) {}
  B b;
  A a;
};

int main() {
  {
    int x = 13;
    cout << x

         << endl;
  }
  C c;
  cout << std::bitset<64>(c.b.y) << " " << c.b.y << endl;
}
