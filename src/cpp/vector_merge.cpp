#include <iostream>
#include <vector>

/**
 * Исходные вектора остаются неизменны [сверх тупая реализация]
 * @tparam T
 * @param a
 * @param b
 * @return
 */
template <typename T>
std::vector<T> merge_vectors(std::vector<T> a, std::vector<T> b) {
  std::vector<T> res;
  while (!a.empty() && !b.empty()) {
    T maxi = 0;
    if (a.front() > b.front()) {
      maxi = b.front();
      b.erase(b.begin());
    } else {
      maxi = a.front();
      a.erase(a.begin());
    }
    res.push_back(maxi);
  }
  while (!a.empty()){
    res.push_back(a.front());
    a.erase(a.begin());
  }
  while (!b.empty()){
    res.push_back(b.front());
    b.erase(b.begin());
  }
  return res;
}

int main() {
  std::vector<int> a = {1, 2, 3};
  std::vector<int> b = {2, 5, 6};
  std::vector<int> c = merge_vectors(a, b);
  for (auto& elem : c) std::cout << elem << ' ';
  std::cout << std::endl;
  for (auto& elem : a) std::cout << elem << ' ';

  return 0;
}