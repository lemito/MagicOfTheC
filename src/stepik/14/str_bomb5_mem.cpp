#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

char* replace(const char* src) {
  char* res = (char*)malloc(N* sizeof(char));
  strcpy(res, src);
  size_t watermelon_len = strlen("watermelon");
  size_t bomb_len = strlen("bomb");

  // указатель на начало строки
  char* p = res;

  while ((p = strstr(p, "bomb")) != NULL) {
    // Копируем и сдвигаем:
    memmove(p + watermelon_len, p + bomb_len, strlen(p + bomb_len) + 1);
    memcpy(p, "watermelon", watermelon_len);
    // перескакиваем
    p += watermelon_len;
  }
  return res;
}

int main() {
  char s[N];  // нужно объявить переменную - место для читаемой строки
  char* d;    // указатель на динамический массив, память еще не выделена

  while (NULL != fgets(s, N, stdin)) {  // пока можем прочитать строку
    d = replace(s);                     // тут память выделяем
    printf("+++%s+++\n", d);
    free(d);  // тут память освобождаем
  }
  return 0;
}