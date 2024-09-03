#include <pthread.h>
#include <stdio.h>
#include <windows.h>

pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;  // некий сигнал
pthread_mutex_t mutex;                              // мьютекс

void* do1(void* arg) {
  pthread_mutex_lock(&mutex);
  puts("Я (поток 1) Ждемс");
  pthread_cond_wait(&condvar, &mutex);
  puts("Я (поток 1) че-то сделал");
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void* do2(void* arg) {
  pthread_mutex_lock(&mutex);
  puts("Я (поток 2) начал че то делать");
  puts("2тыкаю сигнал");
  pthread_cond_signal(&condvar);
  puts("2Тыкнул сигналом");
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(void) {
  pthread_t th1, th2;
  int th1_id = 0, th2_id = 1;
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&th1, NULL, do1, &th1_id);
  Sleep(2);
  pthread_create(&th2, NULL, do2, &th2_id);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  pthread_mutex_unlock(&mutex);
  return 0;
}