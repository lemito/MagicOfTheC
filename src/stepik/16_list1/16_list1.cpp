/**
 * Односвязный список на C++, иммитирующий дек, очередь и стек
 * Для работы на Си требуется рефакторинг
 */
#include <cstdio>
#include <cstdlib>
typedef int T;

struct Node {
  T data;
  struct Node* next;

  Node() : data(0), next(NULL) {};
};
struct List {
  Node* root;
  size_t size;

  List() : root(NULL), size(0) {};
  List(Node* r) : root(r), size(1) {};
  void Print() {
    for (Node* p = root; p != NULL; p = p->next) {
      printf("%d ", p->data);
    }
    puts("");
  }
  void Push_front(T obj) {
    Node* new_node = new Node;
    new_node->data = obj;
    new_node->next = this->root;
    this->root = new_node;
    ++this->size;
  }
  void Push_back(T obj) {
    Node* new_node = new Node;
    new_node->data = obj;
    new_node->next = NULL;

    if (this->root == NULL) {
      this->root = new_node;
    } else {
      Node* cur = this->root;

      while (cur->next != NULL) {
        cur = cur->next;
      }

      cur->next = new_node;
    }
    ++this->size;
  }
  T Pop_front() {
    Node* c = this->root;
    if (c == NULL) {
      perror("Список пуст");
      return 0;
    }
    this->root = c->next;
    T res = c->data;
    delete c;
    --this->size;
    return res;
  }

  T Pop_back() {
    // список пуст
    if (this->root == NULL) {
      perror("Список пуст");
      return 0;
    }
    // список из одного элемента
    if (this->root->next == NULL) {
      T res = this->root->data;
      delete this->root;
      this->root = NULL;
      --this->size;
      return res;
    }
    // список из более чем двух элементов
    Node* prev = this->root;
    Node* cur = this->root->next;
    while (cur->next != NULL) {
      prev = cur;
      cur = cur->next;
    }
    T res = cur->data;
    prev->next = NULL;
    --this->size;
    delete cur;
    return res;
  }

  bool IsEmpty() { return this->size == 0 || this->root == NULL; }

  void Clear() {
    while (!this->IsEmpty()) {
      this->Pop_back();
    }
    this->size = 0;
  }

  ~List(){
    Clear();
  }
};
int main() {
  List l;

  l.Push_back(2);
  l.Push_back(3);
  l.Push_back(17);
  l.Push_back(21);
  l.Push_back(22);
  l.Print();
  printf("_%d_", l.Pop_front());
  l.Print();
  printf("_%d_", l.Pop_back());
  l.Clear();
  return 0;
}