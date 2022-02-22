#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;

struct Mystruct
{
  int a;
  const char *b;
  int arr[3];
};

int main()
{
  Mystruct mc = { 1, "abc", 1, 2, 3 };
  int a[] = { 1, 2, 3 };

  std::vector<int> iv = {1, 2, 3};

  std::map<int, std::pair<std::string, int>> m = {
  // nested list-initialization
    {1, { "a", 1 } },
    {2, { "abc", 2 } }
  };


  cout << mc.a << mc.b << mc.arr[0] << mc.arr[1] << mc.arr[2] << endl;
  cout << a << endl;
}
