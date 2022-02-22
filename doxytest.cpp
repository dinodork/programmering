#include <iostream>
#include <bitset>

using std::cout;
using std::endl;
using std::bitset;


/**
   Demonstration of Markdown
   - _italic_
   - __bold__
   - Automatic correction of ampersand: AT&T
   - Automatic code font: `printf()`.
   - ``There is a literal backtick (`) here.``

   ...

> This is a blockquote.

> This is another one.
> This one spans two lines.
*/
class Base {
public:
  int m_int;

/**
  @defgroup AGroupOfMemberFunctions A group of member functions
  @{
*/

  /**
    This member function is in a group.
    @param[in] a The a parameter.
    @param[out] a The b parameter.
  */
  void foo(int * a, int * b) {}

  /// This member function is in a group.
  void fie() {}

/// @}

  /// This member function is not in the group.
  void fum() {}

  /// This member function is virtual.
  virtual void myVirtualFun() {}
};


class Derived : public Base {
public:
  Derived(int myint) : m_myint(myint) {}

  Derived& operator =(const Derived& other) {
    m_int = other.m_int;
    m_myint = other.m_myint;
  };

  void print() { cout << m_myint << ", " << m_int << endl; }
private:
  int m_myint;
};


class DerivedAsWell : public Base {
public:
  Derived(int myint) : m_myint(myint) {}

  Derived& operator =(const Derived& other) {
    m_int = other.m_int;
    m_myint = other.m_myint;
  };

  void print() { cout << m_myint << ", " << m_int << endl; }
private:
  int m_myint;
};

struct Bits {
  unsigned char onebit:1;
  unsigned char twobits:2;
  unsigned char fourbits:4;
  unsigned char padding:1;
  unsigned int kalle_johansson;
}

/**
   The main function.
   _italic_
   __bold__
*/
int main() {
  Derived d1(666), d2(42);
  d1.m_int = 13;
  d2.m_int = 31;
  Derived *pd2 = &d2;
  d1.print();
  d2.print();
  *pd2 = d1;
  pd2->print();
  d2.print();

  Bits bits = { 1, 2, 8, 666 };
  cout << "Sajsen: " << sizeof( bits ) << endl;
}
