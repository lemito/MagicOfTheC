#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace(char* src) {
  size_t watermelon_len = strlen("watermelon");
  size_t bomb_len = strlen("bomb");

  // указатель на начало строки
  char* p = src;

  while ((p = strstr(p, "bomb")) != NULL) {
    // Копируем и сдвигаем:
    memmove(p + watermelon_len, p + bomb_len, strlen(p + bomb_len) + 1);
    memcpy(p, "watermelon", watermelon_len);
    // перескакиваем
    p += watermelon_len;
  }
}

int main() {
  char* d = (char*)malloc(sizeof(char) * 1001);
  while (fgets(d, 1000, stdin) != NULL) {
    replace(d);
    printf("%s", d);
  }
  free(d);
  return 0;
}
