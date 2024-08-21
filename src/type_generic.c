#include <stdio.h>

void testl(long inpt) {
  printf("%ld", inpt);
  putc('\n', stdout);
}
void testi(int inpt) {
  printf("%d", inpt);
  putc('\n', stdout);
}
void testf(float inpt) {
  printf("%.4f", inpt);
  putc('\n', stdout);
}

#define test(X) \
  _Generic((X), long: testl, int: testi, float: testf, default: testi)(X)

int main(int argc, char const *argv[]) {
  long a = 5L;
  int b = 55;
  float c = 5.45;
  test(a);
  test(b);
  test(c);
  return 0;
}
