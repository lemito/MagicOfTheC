#include <complex.h>

#include <iostream>
#include <string>
#include <vector>

/**
 * Функция Max с шаблоном
 * @tparam T Type of element.
 * @param l
 * @param r
 * @return
 */
template <typename T>
inline T Max(const T& l, const T& r) {
  return l > r ? l : r;
}

/**
 * Функция Min с шаблоном
 * @tparam T Type of element.
 * @param l
 * @param r
 * @return
 */
template <typename T>
inline T Min(const T& l, const T& r) {
  return l < r ? l : r;
}

/**
 * Функция Max для vector<T>
 * @tparam T Type of element.
 * @param l
 * @param r
 * @return
 */
template <typename T>
std::vector<T> Max(const std::vector<T>& l, const std::vector<T> r) {
  if (l.size() != r.size()) {
    return l.size() > r.size() ? l : r;
  }
  return l > r ? l : r;
}

/**
 * Структура точки
 * Пусть у нас плоскость может быть целочисленная, double или комплексная
 * @tparam Tx
 * @tparam Ty
 * @tparam Tz
 */
template <typename Tx, typename Ty, typename Tz>
struct Point{
  Tx x;
  Ty y;
  Tz z;
};

int main() {
  // Тесты Max
  std::cout << Max(4, 5) << '\n';
  std::cout << Max(5.3, 5.2) << '\n';
  std::cout << Max(std::string("aba"), std::string("aab")) << '\n';
  // Тесты Min
  std::cout << Min(4, 5) << '\n';
  std::cout << Min(5.3, 5.2) << '\n';
  std::cout << Min(std::string("aba"), std::string("aab")) << '\n';
  // Тесты Max для vector
  std::vector<int> v1 = {1, 2, 3};
  std::vector<int> v2 = {4, 5};
  for (auto& elem : Max(v1, v2)) {
    std::cout << elem << " ";
  }
  std::cout << '\n';
  // Тесты с точкой
  Point<std::complex<double>, int, double> p1 = {1.0 + 2j, 2, 1.25};
  std::cout << p1.x << ' ' << p1.y << ' ' << p1.z;
  std::cout << '\n';
  return 0;
}