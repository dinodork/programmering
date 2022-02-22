#include <iostream>
#include <bitset>

using std::cout;
using std::endl;
using std::bitset;


class Base
{
private:
  virtual void vfoo() { cout << "Base::foo" << endl; }
public:
  friend void foo(Base *);
};


class Derived : public Base
{

private:
  virtual void vfoo() { cout << "Derived::foo" << endl; }

  void bajs() { Base::vfoo(); }

};

void foo(Base *b)
{
  b->vfoo();
};

int main() {

  Base b;
  foo(&b);

//  b.vfoo();

  Derived d;
  foo(&d);
}
