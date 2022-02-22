#include <iostream>
#include <functional>
#include <string>

using std::cout;
using std::endl;

union kalle {
  int i;
  std::string *s;
  int j;
  int k;
  int l;
  int m;
  int n;
  int o;
  int p;
};

int main() {
  kalle k1;
  k1.i = 42;
  std::string apa = "hej hopp";
  cout << "Kellermeister " << k1.i << endl;
//  cout << "Kellermeister " << *k1.s << endl;
  k1.s = &apa;
  cout << "Kellermeister " << k1.i << endl;
  cout << "Kellermeister " << *k1.s << endl;
  cout << "Stor som " << sizeof(kalle) << endl;
  cout << "Stor som " << sizeof(k1) << endl;

}
