#include <iostream>
#include <string>

using std::cout;
using std::endl;

template<typename T>
struct Base {
  Base(T t) : a(t) {}
  T a;
};

template<typename T>
struct Descendent : public Base<T>
{
  Descendent(T t) : Base<T>(t) {}
};

using D2 = Descendent<int>;

int main() {

  Descendent<int> bla(1);
  D2 blabla(2);
  cout << "kuk " << sizeof(bla) << endl;
}

 
