#include <assert.h>
#include <stdio.h>

int cmp_int(const void *p1, const void *p2) {
  int *c1 = (int *)p1;
  int *c2 = (int *)p2;
  if (*c1 < *c2) {
    return -1;
  } else if (*c1 > *c2) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  int x, y, res;
  scanf("%d%d", &x, &y);

  res = cmp_int(&x, &y);

  if (res < 0)
    res = '<';
  else if (res > 0)
    res = '>';
  else
    res = '=';

  printf("%c\n", res);

  int a[] = {3, -7, 5, 3};
  assert(cmp_int(a, a+1) > 0);
  assert(cmp_int(a, a+2) < 0);
  assert(cmp_int(a, a+3) == 0);

  return 0;
}