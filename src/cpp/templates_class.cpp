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
    for (const auto& row : data) {
      if (row.size() > maxSize) {
        maxSize = row.size();
      }
    }

    for (auto& row : data) {
      row.resize(maxSize);
    }
  }

 public:
  Matrix(const std::vector<std::vector<T>>& d) : data(d) { PreInit(); }
  Matrix(size_t rows, size_t columns) {
    data.resize(rows);
    for (auto& row : data) row.resize(columns);
  }

  std::vector<T>& operator[](size_t i) { return data[i]; }
  T& operator () (size_t i, size_t j) {
    return data[i][j];
  }
  auto begin() const {
      return data.begin();
  }
  auto end() const {
    return data.cend();
  }
  size_t GetRows() { return data.size(); }
  size_t GetColumns() {
    if (data.empty()) return 0;
    return data[0].size();
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
  for (const auto& row : m1) {
    for (const auto& elem : row) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}