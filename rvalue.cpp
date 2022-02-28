#include <functional>
#include <iostream>

using std::cout;
using std::endl;

struct Sture {
  int i;
};

template <typename T> int foo(T &&t) {
  cout << "foo: " << t.i << endl;
  t.i = 3;
  cout << "foo: " << t.i << endl;
}

int main() {
  Sture sture{666};
  foo(sture);
  cout << "---" << endl;
  const Sture sture2{13};
  foo(sture2);
}
