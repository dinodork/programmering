#include <iostream>
#include <bitset>
#include <functional>


using std::cout;
using std::endl;

void printit(int n, const char *a) { cout << n << " : " << a << endl; }
void printit(int n, const char *a, const char *b) { cout << n << " : " << a << ", " << b << endl; }

template<typename ... Types>
int foo(int no, Types ... args)
{
  printit(no, args...);
}

template<int I>
class Bajs {};

template<typename T>
class Bajs {};

int main()
{
  cout << "hello" << endl;
  foo(42, "apa");
  foo(42, "kaka", "burk");
}
