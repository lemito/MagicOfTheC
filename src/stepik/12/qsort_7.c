#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 1001
#define inf INT_MAX

int cmp_int(const void *p1, const void *p2) {
  int *c1 = (int *)p1;
  int *c2 = (int *)p2;
  if (*c1 < *c2) {
    return -1;
  } else if (*c1 > *c2) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  int n;
  int arr[ARR_SIZE];
  int arr_second[ARR_SIZE];
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
    arr_second[i] = 0;
    if (arr[i] % 2 != 0) {
      arr_second[i] = arr[i];
      arr[i] = inf;
    }
  }

  qsort(arr, n, sizeof(int), cmp_int);

  int j = 0;
  for (int i = 0; i < n; ++i) {
    if (arr_second[i] != 0) {
      printf("%d ", arr_second[i]);
    } else {
      printf("%d ", arr[j]);
      ++j;
    }
  }
}