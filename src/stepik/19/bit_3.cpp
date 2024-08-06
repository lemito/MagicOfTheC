#include <stdio.h>

#define GENDER 00000001
#define HAT (1 << 2)
#define HAIR (6 << 3)

int main() {
  unsigned char inpt;
  scanf("%hhx", &inpt);
  //  printf("%d\n", inpt & HAIR);
  if ((inpt & HAIR) == 48)
    printf("bk\n");
  else if ((inpt & HAIR) == 32)
    printf("bw\n");
  else if ((inpt & HAIR) == 16)
    printf("rd\n");
  else if ((inpt & HAIR) == 0)
    printf("bn\n");
  return 0;
}

/// Эталонное решение
/*
#include <stdio.h>

int main()
{
  unsigned int x;
  scanf("%x", &x);

  char * hair[] = {"bn", "rd", "bw", "bk"};

  printf("%s\n", hair[x >> 4 & 3]);

  return 0;
}
 */