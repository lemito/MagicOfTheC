/**
 * Стек, но ООП.
 * Переделывается в C несложно -
 * Stack st;
 * Stack* st_ptr = &st;
 * И переделать сами функции
 *
 * Версия на статическом массиве
 */
#include <cstddef>
#include <cstdio>
#include <cstring>

#define N 8
// тут тоже на С++ можно использовать template <typename T>
typedef int T;

// тут может быть и class, но, оказывается, struct также может - а для учения
// это даже удобнее - двустороняя связь с Си
struct Stack_static {
  // может быть заменено на std::vector
  T data[N] = {};
  size_t size;

  // это init в види инициализирующего списка, в Си - все в функции
  Stack_static() : size(0) { memset(this->data, 0, sizeof(T)); }
  void Print() {
    for (size_t i = 0; i < this->size; ++i) {
      printf("%d ", this->data[i]);
    }
    puts("");
  }
  void Push(T obj) {
    this->data[this->size] = obj;
    ++this->size;
  }
  T Pop() { return this->data[--this->size]; }
  T Get() { return this->data[this->size - 1]; }
  bool Is_empty() const { return this->size == 0; }

  bool Is_full() const { return this->size == N; }

  void stack_clear() {
    this->size = 0;
    memset(this->data, 0, sizeof(T));
  }

  size_t Size() const { return this->size; }

  ~Stack_static(){
    this->stack_clear();
  }
};



typedef struct Stack_ {
  // в C инициализация не нужна
  T a[N];
  size_t size;
} Stack;

void stack_print(Stack* st) {
  for (size_t i = 0; i < st->size; ++i) {
    printf("%d ", st->a[i]);
  }
  puts("");
}

void stack_init(Stack* st) {
  st->size = 0;
  memset(st->a, 0, sizeof(T));
}

void stack_push(Stack* st, T data) {
  st->a[st->size] = data;
  ++st->size;
}

T stack_pop(Stack* st) {
  T res = st->a[st->size - 1];
  --st->size;
  return res;
}

T stack_get(Stack* st) {
  T res = st->a[st->size - 1];
  return res;
}

bool stack_is_empty(Stack* st) { return st->size == 0; }

bool stack_is_full(Stack* st) { return st->size == N; }

void stack_clear(Stack* st) {
  st->size = 0;
  memset(st->a, 0, sizeof(T));
}

size_t stack_size(Stack* st) { return st->size; }

int main() {
  /*
    Stack st;
    Stack* st_ptr = &st;
    stack_init(st_ptr);
    printf("empty: %s\n", stack_is_empty(st_ptr) ? "YES" : "NO");  // YES
    stack_push(st_ptr, 5);
    stack_push(st_ptr, 7);
    stack_push(st_ptr, 9);
    stack_print(st_ptr);
    printf("%d\n", stack_pop(st_ptr));
    stack_print(st_ptr);
    printf("empty: %s\n", stack_is_empty(st_ptr) ? "YES" : "NO");  // NO
    printf("full: %s\n", stack_is_full(st_ptr) ? "YES" : "NO");    // NO
    stack_push(st_ptr, 5);
    stack_push(st_ptr, 7);
    stack_push(st_ptr, 9);
    stack_push(st_ptr, 5);
    stack_push(st_ptr, 7);
    stack_push(st_ptr, 9);
    printf("full: %s\n", stack_is_full(st_ptr) ? "YES" : "NO");  // YES
  */
  Stack_static st1;
  printf("%zu\n", st1.Size());
  st1.Push(5);
  st1.Push(7);
  st1.Push(9);
  printf("%zu\n", st1.Size());
  st1.Print();
  printf("%d\n", st1.Pop());
  printf("%zu\n", st1.Size());
  st1.Print();
}