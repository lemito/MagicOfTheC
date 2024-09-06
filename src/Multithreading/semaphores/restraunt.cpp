#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>

#define NULL nullptr

/**
 *
 */
sem_t sema;

void* chef(void* arg) {
  puts("Breakfast done!");
  sem_post(&sema);
  Sleep(2);
  puts("Bussines lunch done!");
  sem_post(&sema);
  Sleep(2);
  puts("Dinner done!");
  sem_post(&sema);
  Sleep(2);
  return NULL;
}

void* client(void* arg) {
  sem_wait(&sema);
  puts("Eating breakfast");
  sem_wait(&sema);
  puts("Eating lunch");
  sem_wait(&sema);
  puts("Eating dinner");
  return NULL;
}

int main() {
  sem_init(&sema, 0, 0);
  pthread_t th1, th2;

  pthread_create(&th2, NULL, client, NULL);
  Sleep(2);
  pthread_create(&th1, NULL, chef, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  sem_destroy(&sema);

  return 0;
}