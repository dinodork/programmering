#include <iostream>
#include <string>
#include <type_traits>

using std::cout;
using std::endl;

template <bool Actually_disable> struct Disable {};

template <> struct Disable<true> { using type = int; };

struct T {
  enum { int_t, float_t, string } type;
  template <typename Integer,
            std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
  T(Integer) : type(int_t) {}

  template <
      typename Floating,
      std::enable_if_t<std::is_floating_point<Floating>::value, bool> = true>
  T(Floating) : type(float_t) {} // OK

  template <Disable<false>::type = 0> T(const char *) : type(string) {}
};

int main() {
  cout << "Hello world!" << endl;

  T t1(42);
  T t2(4.2);
  //  T t3<3>("hello");

  cout << "t1.type = " << t1.type << endl;
  cout << "t2.type = " << t2.type << endl;
}
