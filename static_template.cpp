#include <cstddef>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits>

using std::cout;
using std::endl;

class Base {
public:

};

class Derived1 : public Base {

};

class Derived2 : public Base {
public:
};

template<typename Class, const char *Name>
const char *get_name(const Class &c) { return Name; }

template<>
const char *get_name<Derived1, "d1">(const Derived1 &c) { return Name; }

int main()
{
  Derived1 d1, d2;
  cout << "Hello " << get_name(d1) << endl;
//  cout << "Hello " << d2.the_name() << endl;
}
