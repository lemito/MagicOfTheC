#include <iostream>
#include <map>
#include <string>
std::string intToRoman(int num) {
  const int n[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  const std::string s[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                     "XL", "X",  "IX", "V",  "IV", "I"};
  int i = 0;
  std::string str;
  while (num > 0) {
    if (num >= n[i]) {
      str.append(s[i]);
      num -= n[i];
    } else {
      i++;
    }
  }
  return str;
}
int romanToInt(const std::string& s) {
  std::map<std::string, int> mp;
  for (int i = 0; i < 4000; ++i) mp[intToRoman(i)] = i;
  return mp[s];
}
int main() {
  std::cout << romanToInt("MMCCCXLIX");
  return 0;
}