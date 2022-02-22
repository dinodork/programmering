#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using std::cout;
using std::endl;

struct Klass {
  
  enum class bitmap: unsigned char
  {
    APA = 0x01,
    KAKA = 0x02,
    BURK = 0x04
  };
  
  constexpr bitmap operator| (bitmap x, bitmap y)
  {
    using Type = std::underlying_type<bitmap>::type ;
    return bitmap(Type(x) | Type(y));
  }
};
int main()
{
  bitmap b(Klass::bitmap::APA | Klass::bitmap::BURK);
  cout << "Hello " << (int)b << endl;
}
