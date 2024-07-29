#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main() {
  char word[1001];
  bool flag = false;
  while (scanf("%1000s", word) == 1) {
    if (strcmp(word, "bomb") == 0) {
      flag = true;
    }
  }

  if (flag) {
    printf("YES");
  } else {
    printf("NO");
  }

  return 0;
}
