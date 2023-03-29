#include <iostream>
#include <string>

using std::cout;
using std::endl;

struct MyClass { int a; };

void foo(MyClass &&mc) {}
  
int main() {
  for (auto i[1,2]
  MyClass mc{42};
  MyClass &mcl = mc;
//  foo(mcl);
  foo(std::move(mcl));
  cout << "Hello world " << mc.a << endl; }
