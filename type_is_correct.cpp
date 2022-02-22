#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using std::cout;
using std::endl;


constexpr int my_find(const char* s, int pos = 0)
{
  return s[0] == '\0' ? -1 : (s[0] == '%' ? pos : my_find(s + 1, pos + 1));
}

template<typename T, char U> class typeIsCorrect {
public:
  bool value;
  constexpr typeIsCorrect(const char* format, T t) :
    value(format[my_find(format) + 1] == U)
  {}
};

template<> class typeIsCorrect<int, 'i'> {
public:
  bool value;
  constexpr typeIsCorrect(const char* format, int) :
    value(format[my_find(format) + 1] == U)
  {}
};

int main()
{
  static_assert(my_find("bajskorv") == -1, "Hej hej");
  static_assert(my_find("bajs%") == 4, "Hej hej");
//  static_assert(typeIsCorrect("bajs%s", "hej").value, "Hej hej");
//   static_assert(typeIsCorrect("bajs%i", 1), "Wrong type for %i");

  typeIsCorrect<int, 'i'> tic("apa", 1);

  // MY_PRINTF("bajs%s\n", "korv");
  // MY_PRINTF("bajs%i\n", 42);
  // MY_PRINTF("bajs  %s  %i\n", "korv", 1);
}
