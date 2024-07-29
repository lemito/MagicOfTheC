#include <malloc.h>
#include <stdio.h>
#include <string.h>

int main() {
  char* word;  // строка целиком
  int cnt = 0;
  scanf("%m[^$]s", &word);

  char* p = word;
  while ((p = strstr(p, "bomb")) != NULL) {
    cnt++;
    p+=4;
  }

  printf("%d", cnt);

  free(word);

  return 0;
}
