#include <array>
#include <iostream>
#include <vector>
using std::cout;

template <size_t Size>
constexpr std::vector<std::vector<int>>
to_vectors(std::initializer_list<int[Size]> rows) {
  cout << "a apa\n";
  std::vector<std::vector<int>> res;
  for (auto row : rows) {
    cout << "a row " << row << "\n";
    //    res.push_back(row);
  }
  return {};
}

class Matrix {
public:
  using Row = std::vector<int>;

  Matrix(int rowcount, int columncount)
      : m_rows(rowcount, std::vector<int>(columncount)) {}
  /*
    template <size_t Size>
    constexpr Matrix(std::initializer_list<int[Size]> &&rows) : m_rows(rows) {}
  */
  template <size_t Column_count, typename Row_type>
  constexpr Matrix(std::array<Row_type, Column_count> &&rows)
      : m_rows(to_vectors(rows)) {}

  size_t row_count() const { return m_rows.size(); }
  size_t column_count() const { return m_rows[0].size(); }

  std::vector<Row> rows() { return m_rows; }
  const std::vector<Row> &rows() const { return m_rows; }

  Matrix operator*(const Matrix &rhs) const {
    size_t size = m_rows[0].size();
    Matrix res(row_count(), rhs.column_count());
    for (size_t i = 0; i < row_count(); ++i)
      for (size_t j = 0; j < rhs.column_count(); ++j)
        for (size_t k = 0; k < column_count(); ++k)
          res[i][j] += m_rows[i][k] * rhs.m_rows[k][j];
    return res;
  }
  const Row &operator[](size_t n) const { return m_rows[n]; }
  Row &operator[](size_t n) { return m_rows[n]; }

private:
  std::vector<Row> m_rows;
};

void print(const Matrix m) {
  for (auto row : m.rows()) {
    if (row.size() > 0) {
      cout << row[0];
      for (auto i = 1; i < row.size(); ++i)
        cout << ", " << row[i];
    }
    cout << "\n";
  }
}

int main() {

  std::array<int, 3> arr = {1, 2, 3};
  std::vector<int> vq(arr.begin(), arr.end());

  std::vector<std::vector<int>> v = {{1}};
  Matrix m1{{1, 3},  //
            {4, -1}, //
            {-5, 10}};

  Matrix m2{{2, 1}, //
            {-8, 6}};

  print(m1);

  cout << "*"
       << "\n";

  print(m2);

  auto m4 = m1 * m2;
  cout << "="
       << "\n";
  print(m4);
}
