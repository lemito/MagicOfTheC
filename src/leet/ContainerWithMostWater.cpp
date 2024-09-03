#include <iostream>
#include <vector>

int maxArea(std::vector<int>& height) {
  int n = height.size();
  int l = 0, r = n - 1;
  int res = 0;
  while (l < r) {
    res = std::max(res, std::min(height[l], height[r]) * (r - l));
    if (height[l] < height[r])
      l++;
    else
      r--;
  }
  return res;
}

int main() {
  std::vector<int> test1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  std::cout << maxArea(test1);
  return 0;
}