#include <iostream>
#include <initializer_list>

using std::cout;
using std::endl;

int foo(int a, int b) {
  cout << "foo(" << a << "," << b << ")" << endl;
  return 0;
}

class A {
public:
  implicit A(int a, int b) { cout << "A(int, int)" << endl; }
  A(std::initializer_list<int> list) { cout << "A(initializer_list)" << endl; }
};

int main() {

  cout << "Hello, world!" << endl;
  foo(1,2);
  foo({1},{2});
  A a = {1,2};
}
