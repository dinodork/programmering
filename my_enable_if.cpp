#include <iostream>
#include <string>
#include <type_traits>

using std::cout;
using std::endl;

template <bool B, class T = void> struct my_enable_if {};

template <class T> struct my_enable_if<true, T> { typedef T type; };

template <bool B, class T = void>
using my_enable_if_t = typename my_enable_if<B, T>::type;

struct T {
  enum { int_t, float_t, string } type;

  template <typename Integer,
            typename my_enable_if<std::is_integral<Integer>::value,
                                  bool>::type = true>
  T(Integer) : type(int_t) {}

  template <typename Floating,
            typename my_enable_if<std::is_floating_point<Floating>::value,
                                  bool>::type = true>
  T(Floating) : type(float_t) {} // OK

  //  template <typename String, my_enable_if<false, bool>::type = true>
  //  T(String) : type(string) {}
};

template <bool EnableMe, typename my_enable_if<EnableMe, bool>::type = true>
void foo() {
  cout << "foo" << endl;
}

int main() {
  cout << "Hello world!" << endl;

  T t1(42);
  T t2(4.2);

  foo<true>();

  cout << "t1.type = " << t1.type << endl;
  cout << "t2.type = " << t2.type << endl;
}
