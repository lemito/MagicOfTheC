#include <stdio.h>
#include <string.h>

int main() {
  char word[1001];
  int max = 0;
  char max_word[1001];

  while (scanf("%1000s", word) == 1) {
    int word_len = strlen(word);
    if (word_len > max) {
      max = word_len;
      strcpy(max_word, word);
    }
  }

  printf("%s %d\n", max_word, max);

  return 0;
}
