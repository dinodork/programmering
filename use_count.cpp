#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::move;

struct MyClass { int a; };

struct Hallare {
  std::shared_ptr<MyClass> _putte;
  Hallare(shared_ptr<MyClass> &&putte) : _putte(putte) {}
};

int main() {
  auto pelle = std::make_shared<MyClass>();
  cout << "Hejkon fejkon " << pelle.use_count() << endl;
  Hallare h(move(pelle));

  cout << "Hejkon fejkon " << pelle.use_count() << endl;
  cout << "Hejkon fejkon " << h._putte.use_count() << endl;
}
