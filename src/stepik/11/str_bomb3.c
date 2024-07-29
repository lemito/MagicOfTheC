#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char* stringtolower(char* s) {
  for (int i = 0; s[i] != '\0'; i++) s[i] = tolower(s[i]);
  return s;
}

int main() {
  char word[1001];
  bool flag = false;
  while (scanf("%1000s", word) == 1) {
    if (strstr(stringtolower(word), "bomb") != NULL) {
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
