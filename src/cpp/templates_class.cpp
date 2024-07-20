#include <iostream>
#include <vector>

template <typename T>
class Matrix {
 private:
  std::vector<std::vector<T>> data;
  size_t rows{};
  size_t columns{};

  void PreInit() {
    size_t maxSize = 0;
    this->rows = data[0].size();
    for (const auto& row : data) {
      if (row.size() > maxSize) {
        maxSize = row.size();
      }
    }

    for (auto& row : data) {
      row.resize(maxSize);
    }

    this->columns = maxSize;
  }

 public:
  Matrix(const std::vector<std::vector<T>>& d) : data(d) { PreInit(); }
  Matrix(size_t rows, size_t columns): rows(rows), columns(columns) {
    data.resize(rows);
    for (auto& row : data) row.resize(columns);
  }

  std::vector<T>& operator[](size_t i) { return data[i]; }
  T& operator()(size_t i, size_t j) { return data[i][j]; }
  auto begin() const { return data.begin(); }
  auto end() const { return data.cend(); }
  size_t GetRows() const { return this->rows; }
  size_t GetColumns() const { return this->columns; }

  /**
   * Переопределение оператора ВВОДА
   * @param stream
   * @param matrix
   * @return
   */
  friend std::istream& operator>>(std::istream& stream, Matrix<T>& matrix) {
    const size_t r = matrix.GetRows();
    const size_t c = matrix.GetColumns();
    for (size_t i = 0; i != r; ++i) {
      for (size_t j = 0; j != c; ++j) {
        stream >> matrix(i, j);
      }
    }
    return stream;
  }

  /**
   * Переопределение оператора ВЫВОДА
   * @param stream
   * @param matrix
   * @return
   */
  friend std::ostream& operator<<(std::ostream& stream, Matrix<T>& matrix) {
    const size_t r = matrix.GetRows();
    const size_t c = matrix.GetColumns();
    for (size_t i = 0; i != r; ++i) {
      for (size_t j = 0; j != c; ++j) {
        stream << matrix(i, j) << ' ';
      }
      std::cout << '\n';
    }
    return stream;
  }
};

int main() {
  Matrix<int> m1({{1, 5}, {5, 8, 9}});
  Matrix<int> m2(3, 3);
  std::cout << m1.GetRows() << "\n";
  std::cout << m1.GetColumns() << "\n";
  std::cout << m2.GetRows() << "\n";
  std::cout << m2.GetColumns() << "\n";
  m2[1][1] = 52;
  std::cout << m2[1][1] << "\n";

  std::cout << m1;
  return 0;
}