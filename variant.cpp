#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>

using namespace std;

template <typename T, typename U> struct is_one_of;

/**
 * A utility type trait for ensuring that a type is one of the std::variant's
 * alternative types.
 */
template <typename T, typename... Ts>
struct is_one_of<T, std::variant<Ts...>>
    : public std::bool_constant<(
          std::is_same_v<std::remove_reference_t<T>, Ts> || ...)> {};

template <typename T, typename... Ts>
constexpr bool is_one_of_v = is_one_of<T, Ts...>::value;

using MyVariant = std::variant<int, string, bool>;
class MyClass {
public:
  template <typename T,
            typename = typename std::enable_if_t<!std::is_same_v<T, MyClass>>>
  explicit MyClass(T &&t) : v_(t) {
    cout << "MyClass()\n";
  }

  MyClass(MyClass &&mc) = default;

  MyClass(const MyClass &mc) = default;

  MyVariant v_;
};

struct A {

  string member{"a"};
};

template <typename T,
          typename = typename std::enable_if_t<!std::is_same_v<T, A>>>
void foo(T &&t) {
  cout << "foo()\n";
}

struct Foo {
  template <typename T, typename = typename std::enable_if_t<!std::is_same_v<
                            remove_reference_t<T>, remove_reference_t<A>>>>
  explicit Foo(T &&t) {
    static_assert(!is_same_v<T &, A>);
    static_assert(!is_same_v<T &&, A>);
    static_assert(!is_same_v<T, remove_reference_t<A>>);
    static_assert(!is_same_v<remove_reference_t<T>, remove_reference_t<A>>);
    cout << "Foo:Foo(" << t.member << ")\n";
  }
};

int main() {
  cout << is_same<bool, bool>::value << endl;
  cout << is_same<bool, int>::value << endl;
  cout << is_same_v<bool, bool> << endl;
  cout << is_same_v<bool, int> << endl;

  foo(42);
  foo(true);
  foo("hej");
  // foo(A());
  A a{"b"};

  foo(a);

  //  Foo f(a);
  //  Foo f2(A{});

  MyClass mcb(false);
  MyClass mci(1);
  MyClass mcs("hello");

  //  MyClass mcc(mcb);
  MyClass mcc2 = mcb;
  auto mcc3(std::move(mcb));

  MyVariant v{42};
  auto p = get_if<int>(&v);
  if (p)
    cout << *p << endl;
}
