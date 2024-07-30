#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  char* a;            // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
  unsigned int n;     // наибольшая степень десяти
  unsigned int size;  // размер выделенной динамической памяти в а
} Decimal;

Decimal* elong_set_int(unsigned int number) {
  // сначала выделим память под саму структуру (фиолетовый прямоугольник)
  Decimal* px = malloc(sizeof(Decimal));

  if (number == 0) {  // 0*10**0
    px->size = 1;
    px->n = 0;
    px->a = malloc(px->size);
    px->a[0] = 0;
    return px;
  }

  // number точно меньше 10 в 100, выделим память с запасом
  px->size = 100;
  px->a = malloc(px->size);

  for (px->n = 0; number > 0; px->n++) {
    px->a[px->n] = number % 10;
    number /= 10;
  }
  px->n--;

  // выделим памяти точно под хранение числа
  px->size = px->n + 1;
  px->a = realloc(px->a, px->size);
  return px;
}
void elong_destroy(Decimal* px) {
  free(px->a);  // освобождаем желтый массив с цифрами
  free(px);     // освобождаем фиолетовый прямогольник, саму структуру
}
void elong_print(Decimal* x) {
  unsigned int n = x->n;
  for (unsigned int i = n; i != -1; i--) {
    printf("%d", x->a[i]);
  }
}

void elong_check(Decimal* p) {
  unsigned int i;
  for (i = 0; i <= p->n; i++)
    if (p->a[i] > 9 || p->a[i] < 0) {
      printf("ERROR: a[%d]=%d\n", i, p->a[i]);
    }
}

Decimal* elong_add(const Decimal* a, const Decimal* b) {
  Decimal* res = malloc((sizeof(Decimal)));
  const Decimal* x;
  const Decimal* y;
  if (a->n >= b->n) {
    x = a;
    y = b;
  } else {
    x = b;
    y = a;
  }

  res->size = x->n + 2;
  res->a = malloc(res->size);
  memset(res->a, 0, res->size);

  res->n = x->n;
  int dop = 0;

  for (unsigned int i = 0; i <= x->n; i++) {
    int sum = x->a[i] + (i <= y->n ? y->a[i] : 0) + dop;
    res->a[i] = sum % 10;
    dop = sum / 10;
  }
  if (dop > 0) {
    res->a[res->n + 1] = dop;
    res->n = res->n + 1;
  }
  return res;
}

int main() {
  Decimal* a;
  Decimal* b;
  Decimal* res;

  a = elong_set_int(147);  // 147
  b = elong_set_int(13);   // 13

  res = elong_add(a, b);  // res = a+b = 147+13 = 160

  elong_print(res);  // print 160

  elong_destroy(a);
  elong_destroy(b);
  elong_destroy(res);

  return 0;
}