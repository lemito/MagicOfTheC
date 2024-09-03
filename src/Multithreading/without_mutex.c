#include <pthread.h>
#include <stdio.h>
#include <windows.h>
/**
 * должно проходить по всем значениям от 1 до 5, а проходит вообще не так
 */
int qwert = 0;  // глобальная переменная, которую все хотят использовать

void* do_something(void* arg) {
  qwert = 1;
  const int id = *(int*)arg;

  for (int i = 0; i < 5; i++) {
    printf("Thread %d: %d\n", id, qwert);
    qwert += 1;
    Sleep(1);
  }
  return NULL;
}

int main(void) {
  pthread_t th1, th2;
  int th1_id = 0, th2_id = 1;

  pthread_create(&th1, NULL, do_something, &th1_id);
  pthread_create(&th2, NULL, do_something, &th2_id);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  return 0;
}