#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

enum stupid { S_FOO, S_BAR, S_BAZ };
enum class clever { FOO = S_FOO, BAR = S_BAZ, BAZ = S_BAZ };

template <char s> void foo() {}

template <typename T> constexpr bool type_is_correct(char, T) { return false; }

template <> constexpr bool type_is_correct<const char *>(char c, const char *) {
  return c == 's';
}

template <> constexpr bool type_is_correct<int>(char c, int) {
  return c == 'i';
}

constexpr int my_find(const char *s, int pos = 0) {
  return s[0] == '\0' ? -1 : (s[0] == '%' ? pos : my_find(s + 1, pos + 1));
}

template <typename Type>
constexpr bool types_are_correct(const char *format_string, Type head) {
  return type_is_correct<Type>(format_string[my_find(format_string) + 1], head);
}

template <typename Type, typename... Types>
constexpr bool types_are_correct(const char *format_string, Type head,
                                 Types... tail) {
  return type_is_correct<Type>(format_string[my_find(format_string) + 1],
                               head) &&
         types_are_correct(format_string + my_find(format_string) + 1, tail...);
  ;
}

template <typename Head>
constexpr void my_printf(const char *format, Head head) {
  size_t pos = my_find(format) + 1;
  for (uint i = 0; i < pos; ++i)
    cout << format[i];

  cout << head << endl;
}

template <const char[] format, typename Head, typename... Tail>
constexpr void my_printf(Head head, Tail... tail) {
  //  constexpr size_t pos = ;
  static_assert(type_is_correct(format[my_find(format) + 1], head),
                "Fuck off!");
  // for (uint i= 0; i < pos; ++i)
  //   cout << format[i];
  //  cout << head;
  my_printf(format, tail...);
}

main() {
  foo<'s'>();

  static_assert(my_find("abc%sdef") == 3, "Piss");

  static_assert(type_is_correct('s', "s"), "Fuck off!");
  static_assert(type_is_correct('i', 1), "Fuck off!");
  static_assert(!type_is_correct('s', 1), "Fuck off!");

  //  static_assert(types_are_correct<const char*>("abc %s", "def"), "Fuck
  //  off!");
  static_assert(types_are_correct("abc %s", "def"), "Fuck off!");
  static_assert(!types_are_correct("abc %s", 1), "Fuck off!");

  static_assert(types_are_correct("abc %s %s", "def", "ghi"), "Fuck off!");
  static_assert(types_are_correct("abc %s %i", "def", 1), "Fuck off!");
  static_assert(types_are_correct("abc %i %s", 1, "def"), "Fuck off!");

  my_printf<"bajs%s\n">("korv");
  // my_printf("bajs%s\n", 1);

  // my_printf("bajs%s %i\n", "korv", "korv");
  // my_printf("bajs%s\n", 1);

  cout << "hello" << endl;
  cout << S_FOO << endl;
  clever c = static_cast<clever>(S_FOO);
  stupid s = static_cast<stupid>(clever::FOO);
}
