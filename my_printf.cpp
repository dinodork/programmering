#include <bitset>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using std::cout;
using std::endl;

constexpr int my_find(const char *s, int pos = 0) {
  return s[0] == '\0' ? -1 : (s[0] == '%' ? pos : my_find(s + 1, pos + 1));
}

template <typename T, char U>
constexpr bool typeIsCorrect(const char *format, T t) {
  return format[my_find(format) + 1] == U;
}

// constexpr bool typeIsCorrect(const char* format, int i)
// {
//   return typeIsCorrect<int, 'i'>(format, i);
// }

template <> constexpr bool typeIsCorrect<int, 'i'>(const char *format, int i);

template <>
constexpr bool typeIsCorrect<const char *, 's'>(const char *format,
                                                const char *s);

// constexpr bool typeIsCorrect(const char* format, const char* s)
// {
//   return typeIsCorrect<const char *, 's'>(format, s);
// }

template <typename Head>
constexpr bool typesAreCorrect(const char *format, Head head) {
  return typeIsCorrect(format, head);
}

template <typename Head, typename... Tail>
constexpr bool typesAreCorrect(const char *format, Head head, Tail... tail) {
  return typeIsCorrect(format, head) &&
         typesAreCorrect(format + my_find(format) + 1, tail...);
}

// void printLeadingChunk

template <typename Head>
constexpr bool my_printf(std::string format, Head head) {
  //  cout << "##instring is '" << format << "'" << endl;
  size_t pos = format.find("%");
  cout << format.substr(0, pos) << head << format.substr(pos + 2) << endl;
}

template <typename Head, typename... Tail>
constexpr bool my_printf(std::string format, Head head, Tail... tail) {
  //  cout << "#instring is '" << format << "'" << endl;
  size_t pos = format.find("%");
  ///  cout << "#first chunk is '" << format.substr(0, pos) << "'" << endl;
  cout << format.substr(0, pos) << head;
  my_printf(format.substr(pos + 2), tail...);
}

#define MY_PRINTF(f, args...)                                                  \
  do {                                                                         \
    static_assert(typesAreCorrect(f, args), "Type does not match");            \
    my_printf(f, args);                                                        \
  } while (false);

int main() {
  static_assert(my_find("bajskorv") == -1, "Hej hej");
  static_assert(my_find("bajs%") == 4, "Hej hej");
  static_assert(typeIsCorrect("bajs%s", "hej"), "Hej hej");
  static_assert(typeIsCorrect("bajs%i", 1), "Wrong type for %i");

  MY_PRINTF("bajs%s\n", "korv");
  MY_PRINTF("bajs%i\n", 42);
  MY_PRINTF("bajs  %s %s %sen", "k", "o", "rv");
}
