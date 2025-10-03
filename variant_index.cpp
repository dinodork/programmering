#include <iostream>
#include <string>
#include <variant>

using std::cout, std::cerr;
using std::endl;

template <typename T> constexpr std::size_t indexOfType(std::size_t) {
  return std::variant_npos;
}

template <typename T, typename U, typename... Us>
constexpr std::size_t indexOfType(std::size_t i) {
  if (std::is_same_v<T, U>)
    return i;
  return indexOfType<T, Us...>(i + 1);
}

template <typename T, typename... VariantTypes>
constexpr std::size_t indexOf(std::variant<VariantTypes...>) {
  return indexOfType<T, VariantTypes...>(0);
}

int main() {
  std::variant<int, std::string> v1 = "abc";

  cout << "Index of int: " << indexOf<int>(v1) << endl;
  cout << "Index of string: " << indexOf<std::string>(v1) << endl;
  cout << "Index of float: " << indexOf<float>(v1) << endl;
}
