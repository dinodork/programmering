#include <algorithm>

size_t left(size_t i) { return ((i + 1) * 2) - 1; }
size_t right(size_t i) { return (i + 1) * 2; }

template <typename ContainerType>
void heapify(ContainerType &v, size_t i, size_t heapsize = 0) {
  if (heapsize == 0)
    heapsize = v.size();
  size_t largest;
  size_t l = left(i);
  size_t r = right(i);

  if (l < heapsize && v[i] < v[l])
    largest = l;
  if (r < heapsize && v[largest] < v[r])
    largest = r;

  if (largest != i) {
    std::swap(v[i], v[largest]);
    heapify(v, largest);
  }
}

template <typename ContainerType> void buildHeap(ContainerType &v) {
  int heapsize = v.size();
  for (int i = heapsize / 2; i >= 0; --i)
    heapify(v, i);
}

template <typename ContainerType> void heapsort(ContainerType &v) {
  buildHeap(v);
  for (int i = v.size() - 1; i >= 0; --i) {
    std::swap(v[0], v[i]);
    heapify(v, 0);
  }
}
