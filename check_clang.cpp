#include <functional>
#include <iostream>

using std::cout;
using std::endl;

int plusone(int x) { return x + 1; }

int foo(int a, std::function<int(int)> f) { return f(a); }

int main() {
  cout << "Hej " << __clang_major__ << '.' << __clang_minor__ << endl;
  return (__clang_major__ < 3) || (__clang_major__ == 3 && __clang_minor__ < 4);
}
