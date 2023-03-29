#include <iostream>
#include <string>

using std::cout;
using std::endl;

class MyClass {
public:
  MyClass() { cout << "MyClass()" << endl; }
  MyClass(const MyClass &) { cout << "MyClass(const MyClass&)" << endl; }
  MyClass(MyClass &&other) {
    cout << "MyClass(MyClass&&)" << endl;
    other.foo();
  }
  MyClass &operator=(const MyClass &other) {
    cout << "=" << endl;
    return *this;
  }
  MyClass &operator=(MyClass &&other) {
    cout << "=&&" << endl;
    return *this;
  }
  void foo() { cout << "foo" << endl; }
  ~MyClass() { cout << "~MyClass" << endl; }
};

bool my_bool_func() { return true; }

int main() {

  MyClass mc;
  mc = mc;
  cout << "mc2:" << endl;
  mc = std::move(mc);
  cout << "mc3:" << endl;
  MyClass mc3((MyClass()));
  mc3.foo();
  cout << "mc4:" << endl;
  MyClass mc4(std::move(mc));
  cout << "kuk" << endl;
}
