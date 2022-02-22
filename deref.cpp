#include <iostream>

using std::cout;
using std::endl;

struct MyClass
{
  virtual int operator * () const { cout << "MyClass::*" << endl; }
};

struct MySubClass : public MyClass
{
  virtual int operator * () const { cout << "MySubClass::*" << endl; }
};

int main()
{
  MyClass * mcp = new MySubClass;
  **mcp;

  MyClass mci = *mcp;
  *mci;
}
