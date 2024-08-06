#include <stdio.h>

#define GENDER 00000001
#define HAT (1 << 2)
#define HAIR (6 << 3)

typedef struct Characterictic {
  unsigned int shift;  // местоположение проверяемого бита
  unsigned int mask;   // для проверки одного бита - 1, двух - 3 (в двоичной 11)
  char** name;         // массив значений
} Characterictic;

int main() {
  unsigned int inpt;
  scanf("%hhx", &inpt);

  Characterictic chars[6] = {
      {0, 1, (char*[]){"fe", "ma"}},  // пол
      {1, 1, (char*[]){"du", "cl"}},  // умный
      {2, 1,
       (char*[]){
           "nh",
           "ha",
       }},                                        // шляпа
      {3, 1, (char*[]){"sk", "tr"}},              // брюки-юбка
      {4, 3, (char*[]){"bn", "rd", "bw", "bk"}},  // цвет волос
      {6, 3, (char*[]){"bu", "ge", "gy", "da"}}   // цвет глаз
  };

  for (size_t i = 0; i < (sizeof(chars) / sizeof(Characterictic)); ++i) {
    unsigned int ix = (inpt >> chars[i].shift) & chars[i].mask;
    printf("%s ", chars[i].name[ix]);
  }

  return 0;
}