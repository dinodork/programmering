#include <compare>
#include <iostream>
#include <string>

using namespace std;

struct B;
struct A {
  A(int i) : _i(i) {}
  int _i;
  std::strong_ordering operator<=>(const A &rhs) const noexcept = default;
  std::strong_ordering operator<=>(const B &rhs) const;
};

struct B {};

std::strong_ordering A::operator<=>(const B &) const {
  return std::strong_ordering::equal;
}

bool compare_em(const A &a1, const A &a2) { return a1 == a2; }

int main() {
  A a1(1), a2(2), a3(3);

  cout << ((A{1} <=> A{2}) == strong_ordering::equal) << endl;
  cout << "1 < 2: " << (A{1} < A{2}) << endl;
  cout << "1 == 2: " << (A{1} == A{2}) << endl;

  //  B() <=> B();
  A(1) <=> A(1);
  A(1) == A(1);
  A(1) <=> B();
}
