#include <stdio.h>

void print_bin(unsigned char x, char end) {
  for (int i = 7; i >= 0; --i) {
    printf("%d", (1&(x>>i)) ? 1 : 0);
  }
  if (end != 0) {
    putchar(end);
  }
}

int main() {
  unsigned char x;
  scanf("%hhu", &x);  // hh используеся для указания, что работа с char

  print_bin(x, '\n');  // напечатать х и в конце напечатать \n

  return 0;
}