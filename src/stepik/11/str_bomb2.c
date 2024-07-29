#include <stdio.h>
#include <string.h>

int main() {
  char word[1001];  // строка целиком
  int cnt = 0;
  while (scanf("%1000s", word) == 1) {
    char* p = word;
    while ((p = strstr(p, "bomb")) != NULL) {
      cnt++;
      p++;
    }
  }

  printf("%d", cnt);

  return 0;
}
