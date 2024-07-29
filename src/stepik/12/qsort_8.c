#include <stdio.h>
#include <math.h>
struct Point {
  int x;
  int y;
};

int cmp_Point(const void* p1, const void* p2);

int main() {
  struct Point a, b;
  scanf("%d%d", &a.x, &a.y);
  scanf("%d%d", &b.x, &b.y);

  int res = cmp_Point(&a, &b);

  if (res < 0)
    printf("<\n");
  else if (res > 0)
    printf(">\n");
  else
    printf("=\n");

  return 0;
}

/**
 * 0 - если точки лежат на равном расстоянии от центра координат,
 * < 0 - если первая ближе второй от центра координат,
 * > 0 - если первая дальше второй от центра координат.
 * @param p1
 * @param p2
 * @return
 */
#include <math.h>
int cmp_Point(const void* p1, const void* p2) {
  struct Point* point1 = (struct Point*)p1;
  struct Point* point2 = (struct Point*)p2;
  double c1 = sqrt(pow(point1->x, 2) + pow(point1->y, 2));
  double c2 = sqrt(pow(point2->x, 2) + pow(point2->y, 2));
  if (c1 < c2) {
    return -1;
  } else if (c1 > c2) {
    return 1;
  } else {
    return 0;
  }
}