#include <stdio.h>
#include <pthread.h>

void* do_something(void* arg) {
  const char* str = (char*)arg;
  for (size_t i = 0; i < 11; ++i)
    puts(str);
  return "0 - all done";
}

int main(void) {
  pthread_t th1, th2;
  void* test1 = "sdfghjklqwertghj";
  void *test2;
  pthread_create(&th1, NULL, do_something, "Meow");
  pthread_join(th1, &test2);
  printf("%s\n", test2);
  pthread_create(&th2, NULL, do_something, test1);
  pthread_join(th2, &test2);
  printf("%s\n", test2);
  // pthread_exit(NULL);
  puts("END");
  return 0;
}