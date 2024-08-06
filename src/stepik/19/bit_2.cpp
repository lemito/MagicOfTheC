#include <stdio.h>

#define GENDER 00000001
#define HAT (1<<2)


int main() {
  unsigned char inpt;
  scanf("%hhx", &inpt);
  printf("%s\n", inpt & HAT ? "ha" : "nh");
  return 0;
}