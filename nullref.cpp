#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

struct Apa {
  Apa(int a) : _a(a) {}
  int _a;
};

struct Burk {
  Burk() : _a(_apa._a), _apa(66) {}

  int _a;
  Apa _apa;
};

int main() {

  Burk burk;
  cout << burk._a << endl;
  string s =
      "pillesnoppaslkjf;gldkjd;flgkjd;flkgj;dsflkgj;dflkgj;dlfkgjdf;lkgjXS";
  s.~string();
  cout << "anus " << s << endl;
}
