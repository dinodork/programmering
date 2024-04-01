//#include <mdspan>
#include </home/martin/gitroot/mdspan/include/mdspan/mdspan.hpp>
#include <vector>

using namespace Kokkos;
using namespace std;

int main() {
  array v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  // View data as contiguous memory representing 2 rows of 6 ints each
  auto ms2 = mdspan(v.data(), extents{2, 6});
  // View the same data as a 3D array 2 x 3 x 2
  auto ms3 = mdspan(v.data(), extents{2, 3, 2});

  // Write data using 2D view
  for (size_t i = 0; i != ms2.extent(0); i++)
    for (size_t j = 0; j != ms2.extent(1); j++)
#if MDSPAN_USE_BRACKET_OPERATOR
      ms2[i, j] = i * 1000 + j;
#else
      ms2(i, j) = i * 1000 + j;
#endif

  // Read back using 3D view
  for (size_t i = 0; i != ms3.extent(0); i++) {
    printf("slice @ i = %lu", i);
    for (size_t j = 0; j != ms3.extent(1); j++) {
      for (size_t k = 0; k != ms3.extent(2); k++)
#if MDSPAN_USE_BRACKET_OPERATOR
        printf("%i ", ms3[i, j, k]);
#else
        printf("%i ", ms3(i, j, k));
#endif
      printf("\n");
    }
  }
}
