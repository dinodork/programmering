#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using std::cout;
using std::endl;
using std::uint8_t;
using std::vector;

template <typename...> struct all_same;

template <> struct all_same<> : std::true_type {};
template <typename T> struct all_same<T> : std::true_type {};

template <typename T1, typename T2, typename... Rest>
struct all_same<T1, T2, Rest...>
    : std::integral_constant<bool, std::is_same<T1, T2>::value &&
                                       all_same<T2, Rest...>::value> {};

template <typename Row_Type = std::uint8_t,
          typename ContainerType = vector<Row_Type>, typename... Ts>
class Character {
public:
  using RowType = Row_Type;
  using ReferenceType = typename ContainerType::reference;
  static int RowCount;

  template <std::enable_if_t<all_same<Ts...>::value, bool> = true>
  explicit constexpr Character(Ts... ts) : _rows({RowType(ts)...}) {}

  RowType row(int i) { return _rows[i]; }
  ReferenceType operator[](std::size_t i) { return _rows[i]; }
  Character &operator^=(const Character &other) {
    for (int i = 0; i < RowCount; ++i)
      _rows[i] ^= other._rows[i];
    return *this;
  }
  size_t rowcount() const { return RowCount; }

private:
  ContainerType _rows;
};

template <typename RowType, typename ContainerType, typename... Ts>
int Character<RowType, ContainerType, Ts...>::RowCount = sizeof...(Ts);

Character cA{
    0b00000000, //
    0b00111100, //
    0b01000010, //
    0b01000010, //
    0b01111110, //
    0b01000010, //
    0b01000010, //
    0b00000000,
};

Character cB{
    0b00000000, //
    0b01111100, //
    0b01000010, //
    0b01111100, //
    0b01000010, //
    0b01000010, //
    0b01111100, //
    0b00000000,
};

template <typename T> void print_row(int rowno, T t) {
  for (int i = 0; i < 8; ++i) {
    cout << ((t[rowno] << i) & (1 << (sizeof(typename T::RowType) * 8 - 1))
                 ? "⬛"
                 : "⬜");
  }
}

template <typename T> void print_rows(int rowno, T t) {
  print_row(rowno, t);
  cout << endl;
}

template <typename T, typename... Ts>
void print_rows(int rowno, T t, Ts... ts) {
  print_row(rowno, t);
  cout << " ";
  print_rows(rowno, ts...);
}

template <typename T, typename... Ts> void print(T t, Ts... ts) {
  for (int i = 0; i < T::RowCount; ++i)
    print_rows(i, t, ts...);
}

template <typename... Ts> void printem(auto msg, Ts... ts) {
  cout << msg << ":" << endl;
  print(ts...);
}

int main() {
  printem("Before", cA, cB);

  cA ^= cB;

  printem("After A ^= B", cA, cB);

  cB ^= cA;

  printem("After B ^= A", cA, cB);

  cA ^= cB;

  printem("After A ^= B", cA, cB);
}
