#include <bitset>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using std::cout;
using std::endl;

template <typename T, char U>
constexpr bool typeIsCorrect(const char *format, T t) {
  return format[0] == U;
}

constexpr bool typeIsCorrect(const char *format, int i);

template <>
constexpr bool typeIsCorrect<const char *, 's'>(const char *format,
                                                const char *s);

int main() { typeIsCorrect("i", 1); }
