#include <iostream>
#include <string>

using std::cout;
using std::endl;

template<typename T>
void foo(const T &t) {
  cout << "foo sajs " << sizeof(typename T::value_type) << std::endl;
}

int main() {

  int arr[3];
  cout << "int sajs " << sizeof(int) << std::endl;
  foo(arr);
  
  cout << "Hello world!" << endl;

}
