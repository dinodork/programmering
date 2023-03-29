#include <iostream>
#include <memory>

using std::cout;
using std::endl;

void foo(std::unique_ptr<int> ptr) {}

int main() {
  foo(std::unique_ptr<int>());
}
