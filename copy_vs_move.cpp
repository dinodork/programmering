#include <iostream>

using std::cout;
using std::endl;

class A {
public:
  A() { cout << "A()" << endl; }
  A(const A &other) { cout << "A(A&)" << endl; }
  A(A &&other) { cout << "A(A&&)" << endl; }
  ~A() { cout << "~A()" << endl; }
};

void foocopy(A a) { cout << "foocopy()" << endl; }

void fooconstref(const A &a) { cout << "fooconstref()" << endl; }

void foomove(A &&a) { cout << "foomove()" << endl; }

int main() {

  cout << "Hello, world!" << endl;

  foocopy(A());
  cout << "---" << endl;
  fooconstref(A());
  cout << "---" << endl;
  foomove(A());
  cout << "---" << endl;
  {
    A a;
    foocopy(a);
  }
  cout << "---" << endl;
  {
    A a;
    foomove(std::move(a));
  }
  cout << "---" << endl;
}
