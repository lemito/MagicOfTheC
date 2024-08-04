/**
 * Пьяница
 * https://stepik.org/lesson/659477/step/2?unit=656913
 */
#include "list2.h"

#define N 1000000

int main() {
  List<int> player1;
  List<int> player2;

  for (size_t i = 0; i < 5; ++i) {
    int inpt;
    std::cin >> inpt;
    player1.Push_back(inpt);
  }
  for (size_t i = 0; i < 5; ++i) {
    int inpt;
    std::cin >> inpt;
    player2.Push_back(inpt);
  }

  for (size_t i = 0; i < N; ++i) {
    if (player1.IsEmpty()) {
      std::cout << "second " << i;
      return 0;
    }

    if (player2.IsEmpty()) {
      std::cout << "first " << i;
      return 0;
    }

    int c1 = player1.First();
    player1.Pop_First();
    int c2 = player2.First();
    player2.Pop_First();

    if ((c1 < c2 && !(c1 == 0 && c2 == 9)) ||
        (c1 == 9 && c2 == 0)) {
      player2.Push_back(c1);
      player2.Push_back(c2);
    } else {
      player1.Push_back(c1);
      player1.Push_back(c2);
    }
  }

  std::cout << "botva";
  return 0;
}
