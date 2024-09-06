#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>

sem_t sema;

#define vptr void *

vptr
read_book (vptr arg)
{
  char *reader_id = (char *)arg;
  int cnt = 2; // количество посетителей
  while (cnt > 0)
    {
      sem_wait (&sema); // ожидаем, когда освободиться место

      printf ("%s enter\n", reader_id);
      printf ("%s read\n", reader_id);
      Sleep (1);
      printf ("%s leave\n", reader_id);

      sem_post (&sema); // освоюождаем место

      cnt--;
      Sleep (1);
    }
  return NULL;
}

int
main (void)
{
  sem_init (&sema, 0, 3); // библиотека трехместная
  pthread_t readers[5];   // а жителей города 5
  pthread_create (&readers[0], NULL, read_book, "Reader 1");
  pthread_create (&readers[1], NULL, read_book, "Reader 2");
  pthread_create (&readers[2], NULL, read_book, "Reader 3");
  pthread_create (&readers[3], NULL, read_book, "Reader 4");
  pthread_create (&readers[4], NULL, read_book, "Reader 5");

  sem_destroy (&sema);

  pthread_exit (NULL);
  return 0;
}