#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using std::cout;
using std::endl;

int main() {
  int arr[3] = {1, 2, 3};
  auto [x, y, z] = arr;
  x = 42;

  cout << "Hallo " << arr[0] << arr[1] << arr[2] << endl;
}
