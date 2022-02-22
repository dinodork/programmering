#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;

class IndentPrinter {
public:
  IndentPrinter(std::string fnname) : m_fnname(fnname) {
    indent();
    cout << ">" << fnname << endl;
    ++s_indent;
  }

  template <typename T> std::ostream &operator<<(T t) {
    indent();
    if (m_line_is_new) {
      cout << '>';
      m_line_is_new = false;
    }

    return cout << t;
  }

  ~IndentPrinter() {
    --s_indent;
    indent();
    cout << "<" << m_fnname << endl;
  }

private:
  void indent() {
    for (int i = 0; i < s_indent; ++i)
      cout << ' ';
  }
  static thread_local int s_indent;
  std::string m_fnname;
  bool m_line_is_new{true};
};

thread_local int IndentPrinter::s_indent = 0;

void quicksort(int *arr, int begin, int end) {

  IndentPrinter ip(__FUNCTION__);
  ip << '[' << begin << ", " << end << "]" << endl;
  if (end == begin)
    return;
  if (end - begin == 1 and arr[begin] > arr[end]) {
    std::swap(arr[begin], arr[end]);
    return;
  }

  const int pivotpos = begin + (end - begin) / 2;

  quicksort(arr, begin, pivotpos - 1);
  quicksort(arr, pivotpos, end);

  const int pivot = arr[pivotpos];

  int lo = begin, hi = end;
  while (hi > lo) {
    while (arr[lo] <= pivot)
      ++lo;
    while (arr[hi] >= pivot)
      --hi;
    std::swap(arr[lo], arr[hi]);
    ++lo;
    --hi;
  }

  ip << " [" << lo << ", " << hi << "] pivot " << pivot;

  ip << " { " << arr[0];

  for (int i = 1; i < 7; ++i)
    ip << ", " << arr[i];
  ip << " } " << endl;
}

int main() {

  int arr[] = {10, 9, 7, 8, 5, 4, 2};
  cout << "arr before: { " << arr[0];

  for (int i = 1; i < sizeof(arr) / sizeof(int); ++i)
    cout << ", " << arr[i];
  cout << " } " << endl;

  quicksort(arr, 0, sizeof(arr) / sizeof(int) - 1);

  cout << "arr after: { " << arr[0];
  for (int i = 1; i < sizeof(arr) / sizeof(int); ++i)
    cout << ", " << arr[i];
  cout << " } " << endl;
}
