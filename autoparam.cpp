#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>

using std::cout;
using std::endl;

template<typename Func>
void foo(Func func) {
  cout << func(10) << endl;
  cout << func("koka") << endl;
}

int main()
{
  foo([](auto i) { return i + 1; });
  if constexpr (1 == 1) cout << "kueka";
}
