#include <iostream>
#include <string>
#include <bit>

using std::cout;
using std::endl;

bool parity(unsigned int v) {
 
  bool parity = false;  // parity will be the parity of v

  while (v)
  {
    parity = !parity;
    v = v & (v - 1);
  }
  return parity;
}

void print_parity(unsigned int v) {
  cout << "popcount(" << v << ") = " << std::popcount(v) << ", ";
  cout << "parity(" << v << ") = " << parity(v)  << endl;
}

int main() {

  cout << "Hello world!" << endl;
  for (int i = 0; i < 20; ++i)
    print_parity(i);
}
