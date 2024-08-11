// TODO: попытаться сломать
#include <assert.h>
#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 200

typedef struct {
  // массив для хранения числа: a[0] * 100^0 + a[1] * 100^1 + .. +  a[n - 1] *
  // 100^(n-1)
  char* dig;
  int n;      // размер числа в разрядах
  char sign;  // знак числа
} LongN;

void cleaner_LongN(LongN* x) {
  free(x->dig);
  x->n = 0;
}

// начало

#define INT_TO_CHAR(i) (i + '0')
#define CHAR_TO_INT(c) (c - '0')

LongN getLongN(char* s) {
  LongN res;
  switch (*s) {
    case '+':  // +123
      res.sign = 0;
      s++;
      break;

    case '-':  // -123
      res.sign = 1;
      s++;
      break;
    default:  // 123
      res.sign = 0;
      break;
  }
  size_t slen = strlen(s);
  res.n = (slen % 2 == 0) ? (int)(slen / 2) : (int)((slen / 2) + 1);
  res.dig = (char*)malloc(sizeof(char) * res.n);
  //  memset(res.dig, 0, res.n);
  for (size_t i = 0; i < slen; i += 2) {
    res.dig[i / 2] = (slen - 2 - i == -1 ? 0 : (s[slen - 2 - i] - '0') * 10) +
                     (s[slen - 1 - i] - '0');
  }
  return res;
}

// ==============================

void test() {
  LongN x = getLongN("-12345");
  printf("\n%d %d %d\n", (int)x.dig[0], (int)x.dig[1], (int)x.dig[2]);

  puts("");
  assert(x.sign == 1);
  assert(x.n == 3);
  assert(x.dig[0] == 45);
  assert(x.dig[1] == 23);
  assert(x.dig[2] == 1);
  cleaner_LongN(&x);
}

int main() {
  //  LongN x = getLongN("-12345");
  //  printf("%d\n", x.sign);
  //  printf("%d\n", x.n);
  test();

  return 0;
}