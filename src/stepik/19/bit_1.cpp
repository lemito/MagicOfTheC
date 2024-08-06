#include <stdio.h>

#define GENDER 00000001

int main() {
  unsigned char inpt;
  scanf("%hhx", &inpt);
  printf("%s\n", inpt & GENDER ? "ma" : "fe");
  return 0;
}