#include <pthread.h>
#include <stdio.h>
#include <windows.h>
/**
 * Теперь сначала поток 0 выведет 1-5, потом 1 выведет числа 1-5
 */
int qwert = 0;  // глобальная переменная, которую все хотят использовать
pthread_mutex_t locker;

void* do_something(void* arg) {
  pthread_mutex_lock(&locker);  // типа показываем, что моя переменная, никто не
                                // трогает, пишем до переменной
  qwert = 1; // оно под защитой
  const int id = *(int*)arg;

  for (int i = 0; i < 5; i++) {
    printf("Thread %d: %d\n", id, qwert);
    qwert += 1;
    Sleep(1);
  }
  pthread_mutex_unlock(&locker);  // освобождаем
  return NULL;
}

int main(void) {
  pthread_t th1, th2;
  int th1_id = 0, th2_id = 1;
  pthread_mutex_init(&locker, NULL);
  pthread_create(&th1, NULL, do_something, &th1_id);
  pthread_create(&th2, NULL, do_something, &th2_id);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  pthread_mutex_unlock(&locker);
  return 0;
}