#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using std::cout;
using std::endl;

template <typename T> void foo(std::initializer_list<T> list)
{
  for (T t : list)
    cout << t;
  cout << endl;
}

int main()
{
  int arr [] = {1.0, 2, 3};
  foo({'a', 'b', 'c'});
}
