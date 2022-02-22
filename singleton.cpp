#include <iostream>
#include <bitset>

using std::cout;
using std::endl;

template<class B, int N>
class A
{
  int m_n;
public:
  A() 
  {
    m_n= N;
  }
  static A singleton;
};

template<typename B, int N> A<B, N> A<B, N>::singleton;

int main()
{
  A<int, 5> *a_ptr= &A<int, 5>::singleton;
  A<char, 5> *a_ptr2= &A<char, 5>::singleton;


//  A<int> a_different_a(42);
  // a_different_a.m_member= 42;
  // cout << a_ptr->m_member << endl;
  // cout << a_different_a.m_member << endl;
}
