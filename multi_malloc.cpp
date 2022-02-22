#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <tuple>
#include <malloc.h>

using std::cout;
using std::endl;

struct Apa {
  int m_a, m_b;
  Apa(int a, int b) : m_a(a), m_b(b) {}
};


template<typename ...CtorArgs>
Apa *makeAnApa(CtorArgs... ctorArgs)
{
  return new Apa(ctorArgs...);
}

template<typename T, typename ...CtorArgs>
Apa *makeAn(CtorArgs... ctorArgs)
{
  return new T(ctorArgs...);
}

template <typename ...Ts>
class Type_holder {};

template<typename T, typename ...CtorArgs>
std::tuple<T*> makeSome(CtorArgs... ctorArgs)
{
  return std::tuple<T*>(new T(ctorArgs...));
}


template<typename T, typename ...Ts, typename ...CtorArgs>
std::tuple<T*, Ts...> makeSome(CtorArgs... ctorArgs)
{
  auto ttt = makeSome<Ts..., CtorArgs...>(ctorArgs...);
  auto newT = new T(ctorArgs...);
  return std::tuple_cat<std::tuple<T*>(newT), ttt>;
}

template<typename T, typename ...Ts>
struct add_pointers {
};

int main()
{
  Type_holder<int, char> th;
  Apa *newApa = makeAnApa(1, 2);
  Apa *newApa2 = makeAn<Apa>(1, 2);
  std::tuple<Apa*> newApa3 = makeSome<Apa>(1, 2);
//  std::tuple<Apa*, Apa> newApa4 = makeSome<Apa, Apa>(1, 2);

  Apa *apa = std::get<0>(newApa3);
  cout << "An apa! " << apa->m_a << ", " << apa->m_b << endl;
}
