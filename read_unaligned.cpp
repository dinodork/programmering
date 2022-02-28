#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using std::cout;
using std::endl;

template <typename T> T read_unaligned(T *value) {
  T t;
  memcpy(&t, value, sizeof(T));
  return t;
}

int main() {
  int a = 1, b = 2, c = 3;
  int x = read_unaligned(&a);
  cout << "x = " << x << endl;
}
