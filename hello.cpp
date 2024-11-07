#include <iostream>
#include <string>

using std::cout, std::cerr;
using std::endl;

int main() {
  const char *p = nullptr;
  cout << "Hello " << p << "world!" << endl;
  cerr << "Hello " << p << "world!" << endl;
}
