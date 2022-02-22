#include <cstddef>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits>

using std::cout;
using std::endl;

constexpr const std::size_t MAX_DATE_STRING_REP_LENGTH =
  sizeof("YYYY-MM-DD AM HH:MM:SS.FFFFFF+HH:MM");

void foo(const char16_t *s) {
  cout << "foo: " << s[0] << endl;
}

int main()
{
  static constexpr char16_t arr[] = u"XXX";
  foo((char16_t[]){'X', 'X'});
}
