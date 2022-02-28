#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using std::cout;
using std::endl;

struct Myclass {
  Myclass() { cout << "Myclass ctor" << endl; }

  Myclass &operator=(Myclass &rhs) { cout << "operator=" << endl; }

  ~Myclass() { cout << "Myclass dtor" << endl; }
};

int main() {
  Myclass a, b;
  a = b;
}
