#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>
/**
 * Сначала запускается главный поток, затем по очереди 1 и 2, завершается
 * главный
 */
sem_t sema;
int32_t res1 = 0;
int32_t res2 = 0;
uint8_t ch = '0';

void* way_first(void* arg) {
  res1 = 1;
  ch = '1';
  puts("Train on first way");
  sem_post(&sema);
  return NULL;
}

void* way_second(void* arg) {
  res2 = 2;
  ch = '2';
  puts("Train on second way");
  sem_post(&sema);
  return NULL;
}

void* main_track(void* arg) {
  puts("Main is waiting");
  sem_wait(&sema);  // ожидаем, когда семафор станет больше 0 и уменьшаем его
  sem_wait(&sema);  // ожидаем, когда семафор станет больше 0 и уменьшаем его
  // поэтому последовательно запускается поток 1, уменьшается, потом поток 2 -
  // уменьшение
  printf("res1 = %d, res 2 = %d, ch = %c\n", res1, res2,
         ch);  // вывод после завершения 1 и 2 потока
  return NULL;
}

int main(void) {
  sem_init(&sema, 0, 0);
  pthread_t th1, th2, th3;
  // запускам третий поток раньше 1 и 2
  pthread_create(&th3, NULL, main_track, NULL);
  Sleep(20);
  pthread_create(&th1, NULL, way_first, NULL);
  pthread_create(&th2, NULL, way_second, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  pthread_join(th3, NULL);

  sem_destroy(&sema);

  return 0;
}