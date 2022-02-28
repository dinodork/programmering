#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using std::cout;
using std::endl;

class Kalsong {};

class KallefieraFn {
  virtual bool execute() = 0;
};

class KalleKallefiera : public KallefieraFn {
  bool execute() { cout << "Kalle kallefierar" << endl; }
};

template <typename T> class Interfacet {
public:
  void kallefiera(T k) { getKallefiera().execute(); };

  virtual KallefieraFn &getKallefiera() = 0;
  int a;
};

class Kalle : public Interfacet {
  KallefieraFn virtual KallefieraFn &getKallefiera(){};
};

class Pelle {
public:
  int b;
};

template <typename T, typename... Ts>
class multimixin : public T, public Ts... {
public:
  int b;

  template <typename Tx> void kallefiera(Tx k) {
    T::kallefiera(k);
    cout << "mmx kallefierar" << endl;
  }

  void foo(T t) { fie(t); }
};

template <typename... T> void foo(T... t);

int main() {
  multimixin<Kalle<Kalsong>> mmx;
  cout << "mmx.kallefiera<Kalsong>(Kalsong())" << endl;
  mmx.kallefiera<Kalsong>(Kalsong());
  cout << "---" << endl;

  Kalle<Kalsong> &k = mmx;
  k.kallefiera(Kalsong());

  multimixin<Kalle<Kalsong>, Pelle> kp;
  mmx.a = 42;
  cout << "Apa kaka burk" << endl;
}
