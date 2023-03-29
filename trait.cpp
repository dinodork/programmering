#include <iostream>
#include <string>

using std::cout;
using std::endl;

struct Printer1 {
  void fie() { cout << "Printer1" << endl; }
};

struct BlajPrinter {
  void fie() { cout << "BlajPrinter" << endl; }
};

struct Blaj {};

template <typename T> struct Traits { using TraitsClass = Printer1; };
template <> struct Traits<Blaj> { using TraitsClass = BlajPrinter; };

template <typename T> class MyClass {
public:
  void foo() { typename Traits<T>::TraitsClass().fie(); }
};

int main() {
  MyClass<Printer1> klasse;
  MyClass<Blaj> lasse;
  klasse.foo();
  cout << "kuk" << endl;
  lasse.foo();
}
