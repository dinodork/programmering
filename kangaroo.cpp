#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

string kangaroo(int x1, int v1, int x2, int v2) {
  if (v2 - v1 == 0)
    return "NO";
  int answer = (v2 * x1 - v1 * x2) / (v2 - v1);
  cout << "[ansert " << answer << "] ";
  return answer >= 0 && ((answer - x1) % v1) == 0 &&
                 ((answer - x2) % v2) == 0 && answer >= max(x1, x2)
             ? "YES"
             : "NO";
}

void runkangaroo(int x1, int v1, int x2, int v2) {
  cout << "x1 : " << x1 << ", v1 : " << v1 << ", x2 : " << x2 << ", v2: " << v2
       << " " << kangaroo(x1, v1, x2, v2) << endl;
}

int main() {
  //  runkangaroo(0, 3, 4, 2);
  //  runkangaroo(14, 4, 98, 2); // 2
  // runkangaroo(2, 1, 1, 2);
  // runkangaroo(0, 3, 4, 2);
  // runkangaroo(21, 6, 47, 3);
  //  runkangaroo(35, 1, 45, 3); // 5 NO
  runkangaroo(43, 2, 70, 2); // 10 NO
}
