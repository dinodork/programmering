#include <iostream>
#include <vector>
#include <assert.h>
#include <memory>

using namespace std;

struct A { int i; };

int main()
{
  A as[3] = {{1}, {2}, {3}};
  std::vector<A*> vec{ &as[0], &as[1], &as[2] };

  for (A *a : vec)
    cout << "En a : " << a->i << endl;

  A newa{666};
  auto it = ++vec.begin();
  *it = &newa;
  
  for (A *a : vec)
    cout << "En a : " << a->i << endl;

}
