#include <iostream>
#include <string>
#include <variant>

using std::cout, std::cerr;
using std::endl;

template<typename Type, typename ...Types, typename ...VariantTypes>
int indexOfType(std::variant<Type, VariantTypes...>) {
  return 0;
}

template<typename Type, typename ...Types, typename VariantType, typename ...VariantTypes>
int indexOfType(std::variant<Type, VariantTypes...>) {
  return 0;
}


int main() {
  std::variant<int, std::string> v1 = "abc";
  cout << "Index of int " << indexOfType<int>(v1) << endl;
  cout << "Index of int " << indexOfType<std::string>(v1) << endl;
  
}
