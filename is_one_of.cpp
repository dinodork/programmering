#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>

using std::cout;

template <typename T, typename U> struct is_one_of;

template <typename T, typename... Ts>
struct is_one_of<T, std::variant<Ts...>>
    : public std::bool_constant<(
          std::is_same_v<std::remove_reference_t<T>, Ts> || ...)> {};

template <typename T, typename... Ts>
constexpr bool is_one_of_v = is_one_of<T, Ts...>::value;

using theVariant = std::variant<int, bool, std::string>;

struct variant_holder {

  theVariant v;
  template <typename T>
  typename std::enable_if_t<is_one_of<T, decltype(v)>::value, void> foo(T &&t) {
    cout << "foo(" << t << ")\n";
  }

  template <typename T>
  typename std::enable_if_t<is_one_of_v<T, decltype(v)>, void> fie(T &&t) {
    cout << "fie(" << t << ")\n";
  }

  template <typename T>
  typename std::enable_if_t<is_one_of_v<T, decltype(v)>, void>
  operator=(T &&t) {
    v = std::forward<T>(t);
  }
};

using namespace std;

int main() {
  variant_holder vh;

  static_assert(is_same_v<bool, remove_reference_t<bool &>>);

  vh.foo(1);
  vh.foo(true);
  vh.foo("hello"s);
  //  vh.foo(1.0);

  bool b = true;
  bool &br = b;
  vh.foo(br);

  vh.fie(1);
  vh.fie(true);
  vh.fie("hello"s);
  //  vh.fie(1.0);

  vh = 42;
  vh.foo(variant_holder());
}
