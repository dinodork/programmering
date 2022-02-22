#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using std::cout;
using std::endl;


template<typename T, char U>
constexpr bool typeIsCorrect(const char* format, T t)
{
  return format[0] == U;  
}

constexpr bool typeIsCorrect(const char* format, int i);

template<>
constexpr bool typeIsCorrect<const char *, 's'>(const char* format, const char* s);


int main()
{
  typeIsCorrect("i", 1);
}
