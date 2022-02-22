#include <iostream>

using std::cout;
using std::endl;

struct Base
{
  virtual void foo(int i);
  virtual void fie(int i);
  virtual void fum(int i);
};

struct Descendent : public Base
{
  void foo(int i) ;//final;
  void fie(int i) ;//override;
  void fum(int i);
};

int main()
{
  cout << "Mina drängar" << endl;
}
