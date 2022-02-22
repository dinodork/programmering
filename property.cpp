#include <iostream>
#include <bitset>

using std::cout;
using std::endl;
using std::bitset;

class MyClass {
public:
  int a;
  int b;
  int c;
};


template<typename PropertyType, PropertyType MyClass::*Property>
class PropertySetter {
public:
  void setProperty(MyClass *, PropertyType value);
};

template<typename PropertyType, PropertyType MyClass::*Prop>
void PropertySetter<PropertyType, Prop>::
setProperty(MyClass *mc, PropertyType value)
{
  mc->*Prop= value;
}

#define PROPERTY_SETTER(Property) \
  PropertySetter<decltype(MyClass::Property), &MyClass::Property>

template<typename Property>
class CoolProperty : PropertySetter<decltype(MyClass::Property), &MyClass::Property>
{};

int main() {

  MyClass mc = { 1, 2, 3 };

  PROPERTY_SETTER(b) moc;

  cout << "mc.a = " << mc.a << endl;
  cout << "mc.b = " << mc.b << endl;
  cout << "mc.c = " << mc.c << endl;
  
  moc.setProperty(&mc, 42);


  cout << "mc.a = " << mc.a << endl;
  cout << "mc.b = " << mc.b << endl;
  cout << "mc.c = " << mc.c << endl;

}
