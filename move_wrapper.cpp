#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::cout;
using std::endl;

class Joey {
public:
  Joey(int *b) : m_b(b) {}
  int m_a;
  std::unique_ptr<int> m_b;
};

class Johnny {
public:
  Johnny(Joey &&joey) : m_joey(std::move(joey)) {}

  Joey m_joey;
};

int main() {
  Joey joey(new int(666));
  Johnny johnny(std::move(joey));
  cout << "knulletiknull" << endl;
}
