#include <assert.h>
#include <functional>
#include <iostream>

using std::cout;
using std::endl;

template <typename T> class Nullable {
public:
  Nullable() : m_has_value(false) {}

  template <typename... Ts>
  Nullable(Ts... ts) : m_has_value(true), m_value(ts...) {}

  bool has_value() const { return m_has_value; }
  T value() {
    assert(m_has_value);
    return m_value;
  }

  std::string to_string() const {
    return m_has_value ? std::to_string(m_value) : "null";
  }

private:
  bool m_has_value;
  T m_value;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Nullable<T> &nullable) {
  out << nullable.to_string();
  return out;
}

template <typename T, typename... Ts> bool any_is_null(T t, Ts... ts) {
  return !t.has_value() || any_is_null(ts...);
}

template <typename T> bool any_is_null(T t) { return !t.has_value(); }

template <typename RT, typename... Ts>
Nullable<RT> apply(std::function<RT(Ts...)> fn, Ts... ts) {
  auto res = fn(ts...);
  //  cout << "aapluy " << res << endl;
  return res;
}

// Wraps something callable in an std::function.
template <typename RT, typename Fn, typename... Ts>
RT applyfuck(RT (*fn)(Ts...), Ts... ts) {
  return apply(std::function<(Ts...)>(fn), ts...);
}

int main() {

  Nullable<int> a = 5;
  Nullable<int> b = 3;
  Nullable<int> null;

  cout << "Hello, world!" << endl;
  cout << "a + b = "
       << apply(std::function<int(int, int)>(std::plus<int>()), 3, 8) << endl;

  cout << "a + b = " << applyfuck(std::plus<int>(), 3, 8) << endl;
}
