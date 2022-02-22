#include <iterator>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>

using std::cout;
using std::endl;


constexpr int arr[] = { 1, 2, 3, 18, 4, 5 };



// template<int N, const int (&Arr)[N], int I = N - 1>
// constexpr bool is_fucking_sorted(const int (Arr)[N]) {
//   return is_sorted<N, Arr, I>::value;
// }

template<size_t N, const int (Arr)[N], size_t I = N - 1>
struct is_sorted {
  static constexpr is_sorted<N, Arr, I - 1> arr{};
  static constexpr bool value = Arr[I] > Arr[I - 1] && arr.value;
};

template<size_t N, const int (Arr)[N]>
struct is_sorted<N, Arr, 1> {
  static constexpr bool value = true;
};

template<const int (Arr)[]>
struct is_sorted_som_Fan {
  static constexpr is_sorted<sizeof(Arr) / sizeof(Arr[0]), Arr, sizeof(Arr) / sizeof(Arr[0])> arr{};
  static constexpr bool value = Arr[I] > Arr[I - 1] && arr.value;
};


static_assert(is_sorted<arr>::value, "Hejsan.");

int main()
{
  cout << "Hello" << endl;
}
