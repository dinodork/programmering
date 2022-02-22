#include <iostream>

using std::cout;

struct Hashbar: HashedId, HashedName {

  int getHashCode() const { return 1; }
  int getHashCode2() { return 1; }
  static int hfn(const Hashbar x){return 4;}
  static int hfn2(const Hashbar x){return 4;}

  Uint32 prevHash<id>;
  Uint32 hashValue<id>() const;

  Uint32 prevHash_by_name<name>;
  Uint32 hashValue<name>() const;

};


template <typename T>
int getHashCode(const T & t) { return t->getHashCode(); }


template<typename T, int (*pekareTillGetHashCode)(const T) >
class HaschKaka {

  void haschibaschi(const T & t)
  {
    cout << "hash " << pekareTillGetHashCode(t);
  }

};


int main() {

  HaschKaka<Hashbar, &Hashbar::hfn> roine2;
  HaschKaka<Hashbar, &Hashbar::hfn2> roine2
;
  std::cout << "Hello World!" << std::endl;
  return 0;
}
