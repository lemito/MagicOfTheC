/**
 * Двусвязный список
 * Цели - такие же, как и у односвязного, только чуть круче, больше функций и возможностей
 * Плохо приспособлен для C
 */
#include <cstdio>
#include <cstdlib>
typedef int T;

struct Node {
  T data;
  struct Node* next;
  struct Node* prev;

  Node() : data(0), next(NULL), prev(NULL) {};
  /**
   *
   * @param next
   * @param data
   * @param prev
   */
  Node(Node* next, T data, Node* prev) : data(data), next(next), prev(prev) {};
};
struct List {
  // всегда околонулевой; схема -
  // https://stepik.org/media/attachments/lesson/308797/dlist_barier_model.png
  Node* root;
  size_t size;

  List() {
    this->root = new Node;
    this->root->prev = this->root->next = this->root;
    this->root->data = 0;
    this->size = 0;
  };
  List(Node* r) : root(r), size(1) {};

  void Print() const {
    for (Node* p = this->root->next; p != this->root; p = p->next) {
      printf("%d ", p->data);
    }
    puts("");
  }

  void Push_back(T obj) {
    Node* head = new Node(this->root, obj, this->root->prev);
    this->root->prev->next = head;
    this->root->prev = head;
    ++this->size;
  }
  /**
   * Вставка после определенной Node
   * @param obj
   * @param it
   */
  void Insert(T obj, Node* it) {
    Node* new_node = new Node(it->next, obj, it);
    it->next = new_node;
    it->next->prev = new_node;
    this->root->prev = new_node;
    ++this->size;
  }
  /**
   * Вставка по позиции
   * @param obj
   * @param pos
   */
  void Insert(T obj, size_t pos) {
    if (pos == 0) {
      Node* new_node = new Node(this->root->next, obj, this->root);
      this->root->next = new_node;
      return;
    }
    Node* cur = this->root;
    for (size_t cnt = 0; cnt < pos; ++cnt) {
      cur = cur->next;
    }
    Node* new_node = new Node(cur->next, obj, cur);
    cur->next = new_node;
    cur->next->prev = new_node;
    ++this->size;
  }

  /**
   * Удаление элемента по итератору
   * @param it
   */
  void Remove(Node* it) {
    it->prev->next = it->next;
    it->next->prev = it->prev;
    --this->size;
    delete it;
  }

  [[nodiscard]] bool IsEmpty() const {
    return this->root->next == this->root && this->root->prev == this->root;
  }

  /**
   * Линейный поиск (по значению)
   * @param obj
   * @return
   */
  [[nodiscard]] Node* l_search(T obj) const {
    Node* res = this->root->next;
    while (res != this->root) {
      if (res->data == obj) {
        return res;
      }
      res = res->next;
    }
    // чтобы возвращал root при отсуствии
    return res;
  }
  /**
   * Поиск по позиции
   * @param ix
   * @return Node*
   */
  [[nodiscard]] Node* search(size_t ix) const {
    Node* cur = this->root;
    for (size_t cnt = 0; cnt < ix + 1; ++cnt) {
      cur = cur->next;
    }
    printf("__%d__\n", cur->data);
    return cur;
  }

  /**
   * Удаление элемента по значению
   * @param obj
   */
  void Remove(T obj) {
    Node* it = l_search(obj);
    Remove(it);
    --this->size;
  }

  void Destroy() {
    Node* cur = this->root->prev;
    while (!this->IsEmpty()) {
      Node* tmp = cur;
      Remove(tmp);
      cur = cur->prev->next;
    }
    this->size = 0;
  }

  ~List(){
    this->Destroy();
  }
};

int main() {
  List ll;
  ll.Push_back(22);
  ll.Push_back(2222);
  //  Node* dvatsatdva = ll.l_search(22);
  //  ll.Insert(5, dvatsatdva);
  ll.Insert(5, (size_t)2);
  ll.Remove(22);
  ll.Print();
  printf("%d", ll.search(1)->data);
  printf("\t%d\t", ll.IsEmpty());
  ll.Destroy();
  return 0;
}
