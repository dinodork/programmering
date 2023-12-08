#include <iostream>

using std::cout;
using std::endl;

template <typename NumberType> NumberType gcd(NumberType n1, NumberType n2) {

  while (n1 != n2) {
    if (n1 > n2)
      n1 -= n2;
    else
      n2 -= n1;
  }

  return n1;
}

template <typename NumberType = int> class RationalHelper;

template <typename NumberType = int> class RationalBase {
public:
  constexpr explicit RationalBase(NumberType n) : RationalBase(n, 1) {}
  constexpr RationalBase(NumberType n, NumberType d)
      : numerator_(n), denominator_(d) {}

  RationalHelper<NumberType> operator+(const RationalBase &other) {
    cout << "RationalHelper::+(" << other.numerator() << "/"
         << other.denominator() << ")" << endl;
    auto cd = gcd(denominator(), other.denominator());
    return {numerator() * cd + other.numerator(), denominator()};
  }

  RationalHelper<NumberType> operator/(const RationalBase &other) {
    return {numerator_ * other.denominator_, denominator_ * other.numerator_};
  }

  RationalHelper<NumberType> operator*(const RationalBase &other) {
    return {numerator_ * other.numerator_, denominator_ * other.denominator_};
  }

  NumberType numerator() const { return numerator_; }
  NumberType denominator() const { return denominator_; }

  void shorten() {
    auto g_c_d = gcd(numerator_, denominator_);
    cout << "shorten " << *this << " gcd = " << g_c_d << endl;
    numerator_ /= g_c_d;
    denominator_ /= g_c_d;
  }

private:
  NumberType numerator_, denominator_;
};

template <typename NumberType = int> class Rational;

template <typename NumberType>
class RationalHelper : public RationalBase<NumberType> {
public:
  using base = RationalBase<NumberType>;
  using base::denominator;
  using base::numerator;

  constexpr RationalHelper(NumberType n, NumberType d) : base(n, d) {}

  explicit operator Rational<NumberType>() const {
    Rational<NumberType> r(numerator(), denominator());
    r.shorten();
    return r;
  }
};

template <typename NumberType>
class Rational : public RationalBase<NumberType> {
public:
  using base = RationalBase<NumberType>;
  using base::denominator;
  using base::numerator;

  constexpr Rational(NumberType n) : base(n) {}
  constexpr Rational(NumberType n, NumberType d) : base(n, d) {}
  constexpr Rational(NumberType n, const char *source_text)
      : base(n), source_text_(source_text) {}

  const char *source_text_;
};

template <typename NumberType>
std::ostream &operator<<(std::ostream &os, const RationalBase<NumberType> &dt) {
  os << dt.numerator();
  if (dt.denominator() != 1)
    os << '/' << dt.denominator();
  return os;
}

template <char... C> double operator""_r() {
  cout << "xxx: ";

  ((cout << ',' << C), ...);
  cout << endl;
  return 0;
}

int main() {
  cout << "hej" << endl;
  Rational r1(42);
  cout << r1 << endl;
  cout << "---" << endl;
  cout << (Rational(3, 5)) << endl;
  cout << Rational(1, 2) + Rational(2, 3) << endl;
  cout << Rational(1, 10) + Rational(4, 10) << endl;
  cout << Rational(3, 5) + Rational(5, 5) + Rational(4, 3) << endl;
  cout << Rational(1, 2) / Rational(1, 2) / Rational(3, 4) << endl;
  cout << 1 / 42_r << endl;

  12_r;
}
