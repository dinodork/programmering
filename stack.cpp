#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;

class MyClass {
public:
  MyClass() { cout << "Hi!" << endl; }

  void foo() { cout << "foo" << endl; }

  ~MyClass() { cout << "Bye!" << endl; }
};

template <typename T> class MySmartPointer {
public:
  MySmartPointer(T *t) : _pointee(t) {}
  ~MySmartPointer() { delete _pointee; }

private:
  T *_pointee;
};

void foo(std::unique_ptr<MyClass> p) {}

void unique_ptr() {
  auto p = std::make_unique<MyClass>(); // returns a unique_ptr<MyClass>
  MyClass *p2 = p.get();                // naked pointer
  MyClass mycopy = *p; // overloaded derereferencing operator, copy semantics
                       //  auto pcopy = p;      // Can't copy a unique_ptr
  auto newp = std::move(p); // But you can move
  if (!p) {
    //...
  } //  implicit conversion overloaded
  //  foo(p);

  foo(std::make_unique<MyClass>());
}

int main() {
  int i = 42;
  int j = 43;
  int *i_ptr = &i;
  int *i_ptr2 = &i;
  int **i_ptr_ptr = &i_ptr2;

  i_ptr_ptr = &i_ptr; // points now to i_ptr
  *i_ptr_ptr = &j;    // i_ptr now points to j

  i_ptr++; // now points to j!

  cout << *i_ptr << endl;
  {
    cout << "references" << endl;
    int i = 42;
    int &i_ref = i;
    int *i_ptr = &i;
    //    delete i_ptr;
    i_ref++; // is now 43
    cout << i << endl;
  }
}
