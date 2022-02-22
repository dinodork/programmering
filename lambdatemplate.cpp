#include <iostream>
#include <string.h>
#include <functional>

using std::cout;
using std::endl;

template<typename T>
void foo(T t, int a) {
  cout << "foo " << t(a) << endl;
}

int twice(int a) { return a * 2; }

auto closure = [] (int a) { return a * 3; };

template<> void foo(decltype(closure), int) {}
template<> void foo(decltype(twice), int) {}

int main() {
  cout << twice(13) << endl;
  foo(twice, 11);
  foo<decltype(closure)>(closure, 2);
}
