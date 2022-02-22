/*
  Build:

`icu-config --cxx --cxxflags --cppflags` icu_ub.cpp `icu-config --ldflags` -o icu_ub -g
*/

#include "unicode/udata.h"
#include "unicode/uregex.h"
#include <assert.h>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

int main() {
  UErrorCode status = U_ZERO_ERROR;
  UParseError upe;

  const UChar pattern[] = {'a'};
  URegularExpression *ure =
    uregex_open(pattern, sizeof(pattern) / sizeof(UChar), 0, &upe, &status);
  assert(status == U_ZERO_ERROR);

  const UChar subject[] = {'a'};
  uregex_setText(ure, subject, sizeof(subject) / sizeof(UChar), &status);
  assert(status == U_ZERO_ERROR);

  uregex_reset(ure, 0, &status);
  assert(status == U_ZERO_ERROR);

  bool found = uregex_find(ure, 0, &status);
  assert(found);
  assert(status == U_ZERO_ERROR);

  const UChar replacement[] = {'$'};
  UChar result[3];
  UChar *result_ptr = result;
  int capacity = sizeof(result);
  uregex_appendReplacement(ure, replacement, sizeof(replacement) / sizeof(UChar), &result_ptr,
                           &capacity, &status);

  assert(status == U_REGEX_INVALID_CAPTURE_GROUP_NAME);

  uregex_close(ure);
}
