#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using std::cout;
using std::endl;


/*
class Complex {
public:
    double r;
    double i;
    Complex() : r(0), i(0) {}
    Complex(double real) : r(real), i(0) {}
    Complex(double real, double img) : r(real), i(img) {}
    Complex(double data[2]) : r(data[0]), i(data[1]) {}
};

*/

/*
class Complex {
public:
  double r;
  double i;
  void Init(double real, double img) {
    this->r = real;
    this->i = img;
  }
  Complex() { Init(0,0); }
  Complex(double real) { Init(real, 0); }
  Complex(double real, double img) { Init(real, img); }
};
*/
/*
class Complex {
public:
  const double r;
  const double i;
  Complex() : Complex(0,0) {}
  Complex(double real) : Complex(real, 0) {}
  Complex(double real, double img) : r(real), i(img) {}
  Complex(double data[2]) : r(data[0]), i(data[1]) {}
};
*/
class Complex {
public:
  constexpr Complex() : Complex(0,0) {}
  constexpr Complex(double real) : Complex(real, 0) {}
  constexpr Complex(double real, double img) : r(real), i(img) {}
private:
  const double r, i;
};


int main()
{
  Complex c;
}
