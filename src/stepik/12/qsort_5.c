#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) {
  char l = *(char*)a;
  char r = *(char*)b;
  if (l < r) return -1;
  else if (l > r) return 1;
  else return 0;
}

int main() {
  char text[1001];
  char c;
  int i = 0;
  while ((c = (char)getchar()) != '.') {
    text[i] = c;
    ++i;
  }
  text[i] = '\0';
  qsort(&text, i, sizeof(char), cmp);
  for (int j = 0; j < i; ++j) {
    putchar(text[j]);
  }
  putchar('.');
  return 0;
}