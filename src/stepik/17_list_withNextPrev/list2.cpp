/**
 * Двусвязный список
 * Цели - такие же, как и у односвязного, только чуть круче, больше функций и
 * возможностей Плохо приспособлен для C
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>

#define attr_MU [[maybe_unused]]
#define attr_ND [[nodiscard]]
#ifdef NULL
#define NULL nullptr
#endif

typedef int T;

struct Node {
  T data;
  /**
  * TODO: попробовать умные указатели
  */
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

  attr_ND inline T get_data() const { return this->data; }

  attr_MU inline void set_data(T obj) { this->data = obj; }

  attr_MU attr_ND Node* Next() const { return this->next; }

  attr_MU attr_ND Node* Prev() const { return this->prev; }
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
      printf("%d ", p->get_data());
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
      this->root->next = this->root->prev = new_node;
      ++this->size;
      return;
    }
    Node* cur = this->root;
    for (size_t cnt = 0; cnt < pos; ++cnt) {
      cur = cur->next;
    }
    Node* new_node = new Node(cur->next, obj, cur);
    cur->next = new_node;
    //
    new_node->prev = cur;
    if (cur->next != NULL) {
      cur->next->prev = new_node;
    }
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

  attr_ND bool IsEmpty() const {
    return this->root->next == this->root && this->root->prev == this->root ||
           this->size == 0;
  }

  /**
   * Линейный поиск (по значению)
   * @param obj
   * @return
   */
  attr_ND Node* l_search(T obj) const {
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
  attr_ND Node* search(size_t ix) const {
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

  void swap(Node* a, Node* b) {
    if (a == b) return;

    Node* a_prev = a->prev;
    Node* a_next = a->next;
    Node* b_prev = b->prev;
    Node* b_next = b->next;

    if (a_next == b) {
      Node* tmp = b->next;
      a->next = tmp;
      if (tmp != NULL) tmp->prev = a;

      b->next = a;
      b->prev = a_prev;

      a->prev = b;
      if (a_prev != NULL) a_prev->next = b;
    } else if (b_next == a) {
      Node* tmp = a->next;
      b->next = tmp;
      if (tmp != NULL) tmp->prev = b;

      a->next = b;
      a->prev = b_prev;

      b->prev = a;
      if (b_prev != NULL) b_prev->next = a;
    } else {
      a->next = b_next;
      a->prev = b_prev;
      if (b_next != NULL) b_next->prev = a;
      if (b_prev != NULL) b_prev->next = a;

      b->next = a_next;
      b->prev = a_prev;
      if (a_next != NULL) a_next->prev = b;
      if (a_prev != NULL) a_prev->next = b;
    }
  }

  ~List() { this->Destroy(); }
};

int main() {
  List ll;
  ll.Push_back(22);
  ll.Push_back(2222);
  ll.Push_back(5);

  //  ll.Insert(5, dvatsatdva);
  //  ll.Insert(5, (size_t)2);
  ll.Push_back(4);
  ll.Push_back(8);
  Node* dvatsatdva22 = ll.l_search(2222);
  Node* dvatsatdva = ll.l_search(4);
  //  ll.Remove(22);
  ll.Print();
  //  printf("%d", ll.search(1)->data);
  //  printf("\t%d\t", ll.IsEmpty());
  ll.swap(dvatsatdva, dvatsatdva22);
  ll.Print();
  //  ll.Destroy();
  return 0;
}