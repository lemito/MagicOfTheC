// TODO: сделать :)
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 200

typedef struct {
  char* dig;  // массив для хранения числа: a[0] * 100^0 + a[1] * 100^1 + .. +
              // a[n - 1] * 100^(n-1)
  int n;      // размер числа в разрядах
  char sign;  // знак числа
} LongN;

LongN getLongN(const char* string) {
  LongN result;
  int n = strlen(string);
  result.sign = string[0] == '-' ? 1 : 0;
  result.dig = (char*)malloc(n * sizeof(char));

  return result;
}

int main() {
  LongN x = getLongN("-12345");
  printf("%d\n", x.sign);
  printf("%d\n", x.n);
  return 0;
}