#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>

using namespace std;

template <typename T, typename U> struct is_one_of;

template <typename T, typename... Ts>
struct is_one_of<T, std::variant<Ts...>>
    : public std::bool_constant<(std::is_same_v<T, Ts> || ...)> {};

template <typename T, typename... Ts>
constexpr bool is_one_of_v = is_one_of<T, Ts...>::value;

struct variant_holder {
  variant<int, bool, string> v;

  template <typename T>
  typename std::enable_if_t<is_one_of<T, decltype(v)>::value, void> foo(T t) {
    cout << "foo(" << t << ")\n";
  }

  template <typename T>
  typename std::enable_if_t<is_one_of_v<T, decltype(v)>, void> fie(T t) {
    cout << "fie(" << t << ")\n";
  }
};

int main() {
  variant_holder vh;

  vh.foo(1);
  vh.foo(true);
  vh.foo("hello"s);
  //  vh.foo(1.0);

  vh.fie(1);
  vh.fie(true);
  vh.fie("hello"s);
  //  vh.fie(1.0);
}
