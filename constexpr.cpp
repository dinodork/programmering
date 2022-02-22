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

template<typename T, char Typecode> class typeMatcher {
public:
  bool value= false;
};

template<> class typeMatcher<int, 'i'> {
public:
  bool value= true;
};
    

template<char Format, typename T>
constexpr bool typeIsCorrect()
{
  return false;
}

template<>
constexpr bool typeIsCorrect<'s', const char*>()
{
  return false;
}

// template<typename t> constexpr bool typeIsCorrect<'s'>(const char* format, const char *);
//template bool typeIsCorrect<int, 'i'>(const char* format, int);

// template<> constexpr bool typeIsCorrect(const char* format, const char* t)
// {
//   return format[my_find(format) + 1] == 's';
// }

// template<> constexpr bool typeIsCorrect(const char* format, int t)
// {
//   return format[my_find(format) + 1] == 'i';
// }

template<typename Head>
constexpr bool typesAreCorrect(const char *format, Head head)
{
  return typeIsCorrect<format, Head>();
}

template<typename Head, typename... Tail>
constexpr bool typesAreCorrect(const char *format, Head head, Tail... tail)
{
  return typeIsCorrect<Head>(format, head).value &&
    typesAreCorrect(format + my_find(format) + 1, tail...);
}

template<typename Head>
constexpr bool my_printf(std::string format, Head head)
{
  size_t pos = format.find("%");
  cout << format.substr(0, pos) << head << endl;
}

template<typename Head, typename... Tail>
constexpr bool my_printf(std::string format, Head head, Tail... tail)
{
  size_t pos = format.find("%");
  cout << format.substr(0, pos) << head;
  my_printf(format.substr(pos), tail...);
}

#define MY_PRINTF(f, args...)                                           \
  do                                                                    \
  {                                                                     \
    static_assert(typesAreCorrect(f, args), "Type does not match");     \
    my_printf(f, args);                                                 \
  } while(false);

int main()
{
  static_assert(my_find("bajskorv") == -1, "Hej hej");
  static_assert(my_find("bajs%") == 4, "Hej hej");
  static_assert(typeIsCorrect<"s", const char*>();
//  static_assert(typeIsCorrect("bajs%s", "hej").value, "Hej hej");
  // static_assert(typeIsCorrect("bajs%i", 1), "Wrong type for %i");

//  MY_PRINTF("bajs%s\n", "korv");
  // MY_PRINTF("bajs%i\n", 42);
  // MY_PRINTF("bajs  %s  %i\n", "korv", 1);
}
