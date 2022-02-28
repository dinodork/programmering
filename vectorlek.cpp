#include <assert.h>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <class T> class no_init_alloc : public std::allocator<T> {
public:
  //  using std::allocator<T>::allocator;
  //  typedef T value_type;
  template <class U, class... Args> void construct(U *, Args &&...) {
    cout << "construct" << endl;
    assert(false);
  }

  template <class U> void destroy(U *p) { cout << "construct" << endl; }
  /*
    void construct(pointer, const_reference)
    {
      cout << "construct" << endl;
      assert(false);
    }
  */
};

template <typename VecType> void init_vec(VecType &v) {
  int *ip = reinterpret_cast<int *>(&v[0]);
  for (int i = 1; i <= 9; ++i)
    ip[i] = i;
}

template <typename VecType> void print_vec(const char *label, VecType &v) {
  cout << label << ": ";
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << ' ';
  }
  cout << endl;
}

class Unitialized_int {
public:
  Unitialized_int() {}
  operator int() { return i; }
  int i;
};

int main() {
  std::vector<int> vec;
  std::vector<Unitialized_int> uvec;
  std::vector<int, no_init_alloc<int>> no_init_vec;

  vec.reserve(10);
  uvec.reserve(10);
  no_init_vec.reserve(10);

  init_vec(vec);
  init_vec(uvec);
  init_vec(no_init_vec);

  vec.resize(10);
  uvec.resize(10);
  no_init_vec.resize(10);
  print_vec("vec", vec);
  print_vec("uvec", uvec);
  print_vec("no_init_vec", no_init_vec);
}
