#include <iostream>

using namespace std;

int *merge(int *arr1, int *arr2, int start1, int end1, int start2, int end2) {
  int ressize = end1 - start1 + end2 - start2;
  auto res = new int[ressize];
  int i1 = start1;
  int i2 = start2;
  for (int i = 0; ressize; ++i)
    if (i1 < end1 && i2 < end2) {
      if (arr1[i1] < arr2[i2])
        res[i++] = arr1[i1++];
      else 
        res[i++] = arr2[i2++];
    }
    else if (i1 < end1)
      res[i++] = arr1[i1++];
    else if (i2 < end2)
      res[i++] = arr2[i2++];
  return res;
}

int *merge_sort(int *i, int start, int end) {
  if (end - start == 1)
    return i;
  int *arr1 = merge_sort(i, start, end / 2);
  int *arr2 = merge_sort(i, end / 2 + 1, end);
  return merge(arr1, arr2, 0, end / 2, end / 2 + 1, end);
}

int main() {
  int a[3] = {3, 2, 1};
  cout << "sorted : " << endl;
  int *res = merge_sort(a, 0, 3);
  for (int i = 0; i < 3; ++i)
    cout << " " << res[i];
  cout << endl;
}
