#include <algorithm>

size_t left(size_t i) { return ((i + 1) * 2) - 1; }
size_t right(size_t i) { return (i + 1) * 2; }

template <typename ContainerType> class Heap;

template <typename ContainerType>
Heap<ContainerType> buildHeap(ContainerType &v);

template <typename ContainerType> class Heap {
  // private:
public:
  Heap(ContainerType &container)
      : container_(container), size_(container.size()) {}

  size_t size() const { return size_; }

  typename ContainerType::value_type extractMax() {
    std::swap(container_.front(), container_.back());
    --size_;
    return container_.back();
  }

  ContainerType &container_;
  size_t size_;
};

template <typename ContainerType>
void heapify(ContainerType &v, size_t i, size_t heapsize = 0) {
  if (heapsize == 0)
    heapsize = v.size();
  size_t l = left(i);
  size_t r = right(i);

  size_t largest;
  if (l < heapsize && v[i] < v[l])
    largest = l;
  else
    largest = i;

  if (r < heapsize && v[largest] < v[r])
    largest = r;

  if (largest != i) {
    std::swap(v[i], v[largest]);
    heapify(v, largest);
  }
}

template <typename ContainerType>
Heap<ContainerType> buildHeap(ContainerType &v) {
  int heapsize = v.size();
  for (int i = heapsize / 2; i >= 0; --i)
    heapify(v, i);
  return Heap(v);
}

template <typename ContainerType> void heapsort(ContainerType &v) {
  buildHeap(v);
  for (int i = v.size() - 1; i >= 0; --i) {
    std::swap(v[0], v[i]);
    heapify(v, 0);
  }
}
