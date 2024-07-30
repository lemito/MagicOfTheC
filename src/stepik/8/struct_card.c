#include <assert.h>
#define TERMINATOR {0, 0}
struct Card {
  char rank;  // достоинство
  char suit;  // масть
};
int check(struct Card* hand) {
  int res = 0;
  while (hand->rank != 0 && hand->suit != 0){
    if (hand->rank == 'Q' && hand->suit == 's') {
      res = 1;
    }
    hand++;
  }
  return res;
}

int main() {
  struct Card hand1[] = {{'Q', 's'}, {'A', 'h'}, {'9', 'd'}, {0, 0}};
  struct Card hand3[] = {{'A', 'h'}, {'Q', 's'}, {'9', 'd'}, {0, 0}};
  struct Card hand2[] = {{'2', 's'}, {'A', 'h'}, {0, 0}};
  assert(1 == check(hand1));
  assert(1 == check(hand3));
  assert(0 == check(hand2));


  return 0;
}