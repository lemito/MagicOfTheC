#include <stdio.h>

typedef struct Rights {
  unsigned int shift;  // местоположение проверяемого бита
  unsigned int mask;   // для проверки одного бита - 1, двух - 3 (в двоичной 11)
  char name;           // значение
} Rights;

typedef unsigned int uint;
#define N 3

int main() {
  Rights rights[] = {{0, 1, 'x'}, {1, 1, 'w'}, {2, 1, 'r'}};
  for (int i = 0; i < N; ++i) {
    uint inpt = getchar() - '0';
    for (int j = N - 1; j >= 0; --j) {
      if ((inpt >> rights[j].shift) & rights[j].mask)
        printf("%c", rights[j].name);
      else
        printf("-");
    }
  }
  return 0;
}

/// эталонное решение
/*
#include <stdio.h>
void print_rwx(unsigned int x)
{
    char a[] = "rwx";
    int i;
    for (i = 0; i < 3; i++, x >>= 1)
        if (!(x & 1))
            a[2-i] = '-';
    printf("%s", a);
}
int main ()
{
    unsigned int x;
    scanf("%o", &x);
    print_rwx(x >> 6);
    print_rwx(x >> 3);
    print_rwx(x);
    printf("\n");
    return 0;
}
 */

/// необычное решение
/*
#include <stdio.h>

int main()
{
  char * permisions = "rwxrwxrwx";
  unsigned int mask;

  scanf("%o", &mask);

  int i;
  for(i=0;i<9;i++)
    printf("%c", mask >> (8-i) & 1 ? permisions[i] : '-');

  return 0;
}
 */