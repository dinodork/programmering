#include <iostream>
#include <string>

using std::cout;
using std::endl;

int leftChildIndexZ(int n, size_t s) { return 2 * n + 1; }

int rightChildIndexZ(int n, size_t s) { return 2 * n + 2; }

int leftChildIndex(int n, size_t s) { return 2 * n - s - 1; }

int rightChildIndex(int n, size_t s) { return 2 * n - s; }

int main() {
  cout << "Hello world!" << endl;

  const size_t s = 15;

  printf("Zero-based:\n");
  for (int i = 0; i < s; ++i) {
    printf("lciz(%i) = %i ", i, leftChildIndexZ(i, s));
    printf("rciz(%i) = %i\n", i, rightChildIndexZ(i, s));
  }

  printf("Zero-based reversed:\n");
  for (int i = 14; i >= 0; --i) {
    printf("lci(%i) = %i\t", i, leftChildIndex(i, s));
    printf("rci(%i) = %i\n", i, rightChildIndex(i, s));
  }
}
