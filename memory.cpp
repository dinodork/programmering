#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class Foo {
public:
  Foo() { cout << "Foo::Foo()" << endl; }
};


namespace std {
template<class...Args>
unique_ptr<Foo> std::make_unique<Foo>(Args&&...);
};

int main() {
  cout << "Hi!" << endl;
  auto foo = std::make_unique<Foo>();
}
