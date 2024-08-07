#include <stdio.h>
#include <stdlib.h>

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

int cmp_int_obr(const void *p1, const void *p2) {
  int *c1 = (int *)p1;
  int *c2 = (int *)p2;
  if (*c1 > *c2) {
    return -1;
  } else if (*c1 < *c2) {
    return 1;
  } else {
    return 0;
  }
}

int main(){
  int n;
  int arr[1000];
  scanf("%d", &n);

  for (int i = 0; i < n; ++i){
    scanf("%d", &arr[i]);
  }

  qsort(arr, n, sizeof(int), cmp_int_obr);

  for (int i = 0; i < n; ++i){
    printf("%d ", arr[i]);
  }
}