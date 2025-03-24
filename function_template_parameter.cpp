#include <functional>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

// using Fn = std::function<void(int)>;
using Fn = void (*)(int);

void foo(int i) { cout << "foo() " << i << endl; }

template <typename T, Fn F = foo> class MyClass {
public:
  MyClass() {
    cout << "Hello world!" << endl;
    F(666);
  }
};

int main() { MyClass<int, foo> mc; }
