#include <cassert>
#include <iostream>
#include <string>
#include <variant>

using std::cout, std::cerr;
using std::endl;

struct comparison_result_t {
  bool is_comparable;
  bool result;
};

template <typename T1, typename T2> struct comparable {
  static constexpr bool value{std::is_same_v<T1, T2>};
};

struct sql_integer_t;
struct sql_smallint_t;

template <> struct comparable<sql_smallint_t, sql_integer_t> {
  static constexpr bool value{true};
};

template <typename T1, typename T2> struct binop_result {};

template <typename T1> struct binop_result<T1, T1> {
  using type = T1;
};

template <> struct binop_result<sql_integer_t, sql_smallint_t> {
  using type = sql_integer_t;
};

template <typename T1, typename T2>
using binop_result_t = typename binop_result<T1, T2>::type;

template <typename T1, typename T2>
struct symmetric_binop_result : public binop_result<T1, T2>,
                                public binop_result<T2, T2> {};

template <typename T1, typename T2>
using symmetric_binop_result_t = typename symmetric_binop_result<T1, T2>::type;

struct sql_smallint_t {
  std::int16_t value;

  bool operator==(sql_smallint_t other) const { return value == other.value; }
  bool operator==(sql_integer_t other) const;

  template <typename OtherType>
  symmetric_binop_result_t<sql_smallint_t, OtherType>
  operator+(const OtherType &other) {
    return {value + other.value};
  }

  template <typename T> comparison_result_t compare_to(T &&other) const {
    if (comparable<sql_smallint_t,
                   std::remove_reference_t<decltype(other)>>::value)
      return {true, *this == other};
    else
      return {false, false};
  }
};

struct sql_integer_t {
  std::int32_t value;

  bool operator==(sql_integer_t other) { return value == other.value; }

  template <typename T> comparison_result_t compare_to(T &&other) {
    if (comparable<decltype(this), decltype(other)>::value)
      return {true, *this == other};
    else
      return {false, false};
  }
};

struct sql_date_t {
  bool operator==(sql_date_t other) { return false; }
};

bool sql_smallint_t::operator==(sql_integer_t other) const {
  return value == other.value;
}

template <typename T> struct comparator {
  const T &v;

  template <typename T2>
    requires comparable<T, T2>::value
  comparison_result_t operator()(T2 o) {
    return {true, v == o};
  };

  comparison_result_t operator()(auto) { return {false, false}; }
};

struct sql_value_t {
  std::variant<sql_smallint_t, sql_integer_t, sql_date_t> value;

  comparison_result_t compare_to(const sql_value_t &other) {
    return std::visit(
        [other](auto v) -> comparison_result_t {
          return std::visit(comparator{v}, other.value);
        },
        value);
  }
};

void test_types() {

  sql_smallint_t val1{42};
  sql_integer_t val2{42};

  auto res = val1.compare_to(val2);

  cout << "comparable : " << res.is_comparable << endl;
  cout << "equal : " << res.result << endl;

  cout << "42 + 42 = " << (val1 + val2).value << endl;
}

int main() {
  sql_value_t val1, val2;

  val1.value = sql_smallint_t{42};
  val2.value = sql_integer_t{42};
  {
    auto res = val1.compare_to(val2);
    cout << "Komaparabla? " << res.is_comparable << endl;
    cout << "Lika? " << res.result << endl;
  }
  {
    auto res = sql_value_t{sql_smallint_t(42)}.compare_to(
        sql_value_t{sql_smallint_t(42)});
    cout << "Komaparabla? " << res.is_comparable << endl;
    cout << "Lika? " << res.result << endl;
  }
  {
    auto res = sql_value_t{sql_integer_t(42)}.compare_to(
        sql_value_t{sql_smallint_t(42)});
    cout << "Komaparabla? " << res.is_comparable << endl;
    cout << "Lika? " << res.result << endl;
  }
  {
    auto res =
        sql_value_t{sql_smallint_t(42)}.compare_to(sql_value_t{sql_date_t()});
    cout << "Komaparabla? " << res.is_comparable << endl;
    cout << "Lika? " << res.result << endl;
  }
  {
    auto res = sql_value_t{sql_date_t()}.compare_to(sql_value_t{sql_date_t()});
    cout << "Komaparabla? " << res.is_comparable << endl;
    cout << "Lika? " << res.result << endl;
  }
}
