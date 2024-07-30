#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 1001
#define inf INT_MAX

int cmp_int(const void *p1, const void *p2) {
  int c1 = *(int*)p1;
  int c2 = *(int*)p2;

  while (c1 != 0 || c2 != 0) {
    int d1 = c1 % 10;
    int d2 = c2 % 10;

    if (d1 != d2) {
      return d1 - d2;
    }
    c1 /= 10;
    c2 /= 10;
  }

  return 0;
}

int main() {
  int n;
  int arr[ARR_SIZE];
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
  }

  qsort(arr, n, sizeof(int), cmp_int);

  for (int i = 0; i < n; ++i) {
    printf("%d ", arr[i]);
  }
}