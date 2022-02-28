#include <assert.h>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <string.h>
#include <vector>

using std::cout;
using std::endl;

constexpr int MINS_PER_HOUR = 60;
constexpr int SECS_PER_MIN = 60;
constexpr int SECS_PER_HOUR = SECS_PER_MIN * MINS_PER_HOUR;

static const std::regex re("^([+-])?([[:digit:]]{2}):([[:digit:]]{2})$",
                           std::regex::optimize);

bool parseTimeZoneOffset(const char *s, int *seconds) {
  std::smatch m;
  std::string str(s);
  if (std::regex_search(str, m, re)) {
    *seconds =
        (m[1] == '-' ? -1 : 1) * (stoi(m[2]) * 60 * 60 + stoi(m[3]) * 60);
    return false;
  } else
    return true;
}

bool parseTimeZoneOffset(std::string str, int *seconds) {
  std::smatch m;
  if (std::regex_search(str, m, re)) {
    *seconds =
        (m[1] == '-' ? -1 : 1) * (stoi(m[2]) * 60 * 60 + stoi(m[3]) * 60);
    return false;
  } else
    return true;
}

bool my_isdigit(char c) { return c >= '0' and c <= '9'; }

bool convert_timezone_to_seconds(const char *str, size_t length, long *offset) {
  const char *end = str + length;
  bool negative;
  ulong number_tmp;
  long offset_tmp;

  if (length < 4)
    return 1;

  if (*str == '+')
    negative = false;
  else if (*str == '-')
    negative = true;
  else
    return true;
  str++;

  number_tmp = 0;

  while (str < end && my_isdigit(*str)) {
    number_tmp = number_tmp * 10 + *str - '0';
    str++;
  }

  if (str + 1 >= end || *str != ':')
    return true;
  str++;

  offset_tmp = number_tmp * MINS_PER_HOUR;
  number_tmp = 0;

  while (str < end && my_isdigit(*str)) {
    number_tmp = number_tmp * 10 + *str - '0';
    str++;
  }

  if (str != end)
    return true;

  offset_tmp = (offset_tmp + number_tmp) * SECS_PER_MIN;

  if (negative)
    offset_tmp = -offset_tmp;

  /*
    Check if offset is in range prescribed by sql standard 2016
    (from -14:00 to 14:00).
  */

  if (number_tmp > 59 || offset_tmp < -14 * SECS_PER_HOUR ||
      offset_tmp > 14 * SECS_PER_HOUR)
    return true;

  *offset = offset_tmp;

  return false;
}

void test(const char *s) {
  int res;
  bool failed = parseTimeZoneOffset(s, &res);
  cout << s << " ";
  if (!failed)
    cout << "res:" << res;
  else
    cout << "FAIL";
  cout << endl;
}

void time(const char *s) {
  int res;
  bool failed = parseTimeZoneOffset(s, &res);
}

void time(std::string s) {
  int res;
  bool failed = parseTimeZoneOffset(s, &res);
}

void time2(const char *s) {
  long int res;
  bool failed = convert_timezone_to_seconds(s, strlen(s), &res);
  assert(!failed);
  assert(res == 36000);
}

int main() {
  std::string s("+10:00");
  for (auto i = 0; i < 10000000; ++i)
    //    time2("+10:00");
    time(s);
  test("+10:11");
  test("-10:00");
  test("10:00");
  test("10:0");
  test("10");
  test("-+10:00");
  test("----10:00");
  test("-+10:00");
  test("123:00");
}
