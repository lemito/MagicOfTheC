#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 1001

struct Point {
  int x;
  int y;
};

int cmp_Point(const void* p1, const void* p2);

int main() {
  int n;
  struct Point points[ARR_SIZE];
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &points[i].x, &points[i].y);
  }

  qsort(points, n, sizeof(struct Point), cmp_Point);

  for (int i = 0; i < n; ++i) {
    printf("%d %d\n", points[i].x, points[i].y);
  }

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
int cmp_Point(const void* p1, const void* p2) {
  struct Point* point1 = (struct Point*)p1;
  struct Point* point2 = (struct Point*)p2;
  double c1 = point1->x * point1->x + point1->y * point1->y;
  double c2 = point2->x * point2->x + point2->y * point2->y;
  if (c1 < c2) {
    return -1;
  } else if (c1 > c2) {
    return 1;
  } else {  // c1 == c2
    if (point1->x < point2->x) {
      return -1;
    } else if (point1->x > point2->x) {
      return 1;
    } else {
      if (point1->y < point2->y) {
        return -1;
      } else if (point1->y > point2->y) {
        return 1;
      } else {
        return 0;
      }
    }
  }
}