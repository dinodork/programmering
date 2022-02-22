#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int left(int i) { return ((i + 1) * 2) - 1; }
int right(int i) { return (i + 1) * 2; }

template <typename Container_type>
void heapify(Container_type &v, int i, int heapsize) {
  int largest = i;
  int l = left(i);
  int r = right(i);

  if (l < heapsize && v[i] < v[l])
    largest = l;
  if (r < heapsize && v[largest] < v[r])
    largest = r;

  if (largest != i) {
    swap(v[i], v[largest]);
    heapify(v, largest, heapsize);
  }
}

template <typename Container_type> void buildHeap(Container_type &v) {
  int heapsize = v.size();
  for (int i = heapsize / 2; i >= 0; --i)
    heapify(v, i, heapsize--);
}

template <typename Container_type> void heapsort(Container_type &v) {
  buildHeap(v);
  for (int i = v.size() - 1; i >= 0; --i) {
    swap(v[0], v[i]);
    heapify(v, 0, i);
  }
}

template <typename Container_type> void test(Container_type &c) {
  heapsort(c);
  cout << "Sorted: ";
  cout << c[0];
  for (int i = 1; i < c.size(); ++i)
    cout << ", " << c[i];
  cout << endl;
}

int main(int, const char **) {
  vector<int> v{51, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
  test(v);
  array<char, 3> arr = {'c', 'b', 'a'};
  test(arr);
}
