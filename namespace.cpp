#include <iostream>

namespace foospace {

struct MyStruct {
  int a;
};

int foo(MyStruct b) { return 42; }

int fie() { return 43; }

} // namespace foospace

int main() {
  using foospace::MyStruct;
  MyStruct b;
  std::cout << "Titta: " << foo(b) << std::endl;
  std::cout << "Titta: " << fie() << std::endl;
}
