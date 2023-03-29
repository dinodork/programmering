#include <bitset>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;

struct FeatureA {
  FeatureA() : x(42) {}
  int x;
};

struct FeatureB {
  explicit FeatureB(FeatureA *a) : y(a->x) {}
  int y;
};

class FullScope {
public:
  FullScope() : b(&a), a(FeatureA()) {}
  FeatureB b;
  FeatureA a;
};

int main() {
  {
    int x = 13;
    cout << x

         << endl;
  }
  FullScope c;
  cout << std::bitset<64>(c.b.y) << " " << c.b.y << endl;
}
