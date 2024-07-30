#include <stdio.h>
#include <string.h>
#define N 100
typedef struct {
  char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
  unsigned int n;  // наибольшая степень десяти
} Decimal;

void elong_print(Decimal x) {
  unsigned int n = x.n;
  for (unsigned int i = n; i != -1; i--) {
    printf("%d", x.a[i]);
  }
}

Decimal add(Decimal x, Decimal y);

void check(Decimal * p)
{
  unsigned int i;
  for (i=0; i <= p->n; i++)
    if (p->a[i] > 9 || p->a[i] < 0) {
      printf("ERROR: a[%d]=%d\n", i, p->a[i]);
    }
}

int main() {
  Decimal x = {{7, 4, 1}, 2};  // set number 147
  Decimal y = {{3, 1}, 1};     // set number 13
  Decimal res;
  check(&x);
  check(&y);
  res = add(x, y);   // res = x+y = 147+13 = 160
  check(&res);
  elong_print(res);  // print 160

  return 0;
}

Decimal add(Decimal x1, Decimal y1) {
  Decimal x, y;
  if (x1.n >= y1.n) {
    x = x1;
    y = y1;
  } else {
    x = y1;
    y = x1;
  }

  Decimal res;
  memset(res.a, 0, sizeof(res.a));
  res.n = x.n;
  int dop = 0;

  for (unsigned int i = 0; i <= x.n; i++) {
    int sum = x.a[i] + (i <= y.n ? y.a[i] : 0) + dop;
    res.a[i] = sum % 10;
    dop = sum / 10;
  }
  if (dop > 0){
    res.a[res.n+1] = dop;
    res.n = res.n+1;
  }
  return res;
}