/**
 * Стек, но ООП.
 * Переделывается в C несложно -
 * Stack st;
 * Stack* st_ptr = &st;
 * И переделать сами функции
 *
 * Версия на динамическом массиве
 */
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define N 10
// тут тоже на С++ можно использовать template <typename T>
typedef int T;

struct Stack_dyn {
  T* data;
  size_t size;
  size_t capacity;

  // это init в види инициализирующего списка, в Си - все в функции
  Stack_dyn() : size(0), capacity(N) {
    this->data = (T*)malloc(this->capacity * sizeof(T));
  }
  void Print() {
    for (size_t i = 0; i < this->size; ++i) {
      printf("%d ", this->data[i]);
    }
    puts("");
  }
  bool Is_empty() const { return this->size == 0; }
  void Push(T obj) {
    if (this->size >= this->capacity) {
      this->capacity += N;
      this->data = (T*)realloc(this->data, this->capacity * sizeof(T));
    }
    this->data[this->size] = obj;
    ++this->size;
  }
  T Pop() {
    // TODO: сделать realloc при Pop
    return this->data[--this->size];
  }
  void clear() {
    free(this->data);
    this->data = NULL;
    this->size = this->capacity = 0;
  }
  ~Stack_dyn() { clear(); }
};

/// Для Си
/*
  Stack * create() {
 Stack * st = malloc(sizeof(Stack));
 init(st);
 return st;
}

Stack * destroy(Stack * st) {
    if (st != NULL) {
        free(st->a);
        free(st);
    }
    return NULL;
}
 */

int main() {
  Stack_dyn st;
  for (size_t i = 0; i < N + 10; ++i) {
    st.Push((int)i);
  }
  puts("");
  st.Print();

  return 0;
}