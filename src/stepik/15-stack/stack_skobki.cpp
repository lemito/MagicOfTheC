#include <cstddef>
#include <cstdio>
#include <cstdlib>
// #include <cstring>
#include <iostream>
#include <string>

#define N 10
// тут тоже на С++ можно использовать template <typename T>
typedef char T;

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


#define IS_OPEN(c) c == '(' || c == '[' || c == '{' || c == '<'
#define IS_CLOSE(c) c == ')' || c == ']' || c == '}' || c == '>'
#define IS_PAIR(c) c == "()" || c == "[]" || c == "{}" || c == "<>"

int main() {
  std::string inpt;
  std::cin >> inpt;
  Stack_dyn st;

  for (char c : inpt) {
    if (IS_OPEN(c)) {
      st.Push(c);
    } else if (IS_CLOSE(c)) {
      if (st.Is_empty()) {
        std::cout << "NO";
        exit(0);
      }
      char p = st.Pop();
      std::string pair = std::string(1, p) + std::string(1, c);
      if (!(IS_PAIR(pair))) {
        std::cout << "NO";
        exit(0);
      }
    }
  }
  if (st.Is_empty()) {
    std::cout << "YES";
    exit(0);
  } else {
    std::cout << "NO";
    exit(0);
  }
}