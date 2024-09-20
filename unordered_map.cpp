#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;

struct MyKey {
  MyKey() { cout << "MyKey::MyKey()\n"; }
};

struct MyClass {
  explicit MyClass(string s) : s_(s) {
    cout << "MyClass::MyClass(" << s << ")\n";
  }
  MyClass(const MyClass &o) { cout << "MyClass::MyClass(const MyClass&)\n"; }
  MyClass(MyClass &&o) { cout << "MyClass::MyClass(const MyClass&)\n"; }
  string s_;
};

int main() {
  std::unordered_map<int, MyClass> map;
  cout << "emplace" << endl;
  map.emplace(std::make_pair(1, "Kalle"));

  cout << "Hello world!" << endl;
  auto it = map.find(1);

  cout << "iterator deref" << endl;
  MyClass &mc = it->second;
  MyClass *mcp = &it->second;
  cout << mcp->s_ << endl;
}
