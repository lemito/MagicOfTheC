#include <stdio.h>
#include <string.h>

//#define IS_DEBUG

#ifdef IS_DEBUG
#define DEBUG(code) (code)
#else
#define DEBUG(code)
#endif

#define N 4
typedef unsigned char uint;

typedef struct Characterictic {
  unsigned int shift;  // местоположение проверяемого бита
  unsigned int mask;   // для проверки одного бита - 1, двух - 3 (в двоичной
  char** name;         // массив значений
} Characterictic;

void print_bin(unsigned char x, char end) {
  for (int i = 7; i >= 0; --i) {
    printf("%d", (1 & (x >> i)) ? 1 : 0);
  }
  if (end != 0) {
    putchar(end);
  }
}
/**
 * ma du ha tr bk da ha bk
 * 11111101
 *
 */

Characterictic chars[6] = {
    {0, 1, (char*[]){"fe", "ma", "", ""}},      // пол
    {1, 1, (char*[]){"du", "cl", "", ""}},      // умный
    {2, 1, (char*[]){"nh", "ha", "", ""}},      // шляпа
    {3, 1, (char*[]){"sk", "tr", "", ""}},      // брюки-юбка
    {4, 3, (char*[]){"bn", "rd", "bw", "bk"}},  // цвет волос
    {6, 3, (char*[]){"bu", "ge", "gy", "da"}}   // цвет глаз
};

uint name2shift(char* inpt) {
  for (size_t i = 0; i < (sizeof(chars) / sizeof(Characterictic)); ++i) {
    for (size_t j = 0; j < N && chars[i].name[j]; ++j) {
      if (strcmp(inpt, chars[i].name[j]) == 0) {
        DEBUG(printf("%zu %zu|", j << chars[i].shift,
                     (j << chars[i].shift) & chars[i].mask));
        return j << chars[i].shift;
      }
    }
  }
  // return 0;
}
int main() {
  char inpt[3];
  uint res = 0b00000000;
  while (scanf("%2s", inpt) == 1) {
    uint valueToAdd = name2shift(inpt);
    res |= valueToAdd;
  }
  printf("%02x", res);
  return 0;
}