/**
 * Двусвязный список
 * Цели - такие же, как и у односвязного, только чуть круче, больше функций и
 * возможностей Плохо приспособлен для C
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>


#define attr_MU [[maybe_unused]]
#define attr_ND [[nodiscard]]

template <typename T>
struct Node {
  T data;
  /**
   * Теперь умные указатели
   */
  std::shared_ptr<Node> next;
  std::shared_ptr<Node> prev;

  // public:
  Node() : data(0), next(nullptr), prev(nullptr) {};
  /**
   *
   * @param next
   * @param data
   * @param prev
   */
  Node(std::shared_ptr<Node> next, T data, std::shared_ptr<Node> prev)
      : data(data), next(std::move(next)), prev(std::move(prev)) {};

  attr_ND inline T get_data() const { return this->data; }

  attr_MU inline void set_data(T obj) { this->data = obj; }

  attr_MU attr_ND std::shared_ptr<Node> Next() const { return this->next; }

  attr_MU attr_ND std::shared_ptr<Node> Prev() const { return this->prev; }
};

template <typename T>
class List {
 private:
  // всегда околонулевой; схема -
  // https://stepik.org/media/attachments/lesson/308797/dlist_barier_model.png
  //  Node* root;
  std::shared_ptr<Node<T>> root;
  size_t size{};

 public:
  /**
   * Доп класс LIterator [шок, но можно делать класс в классе]
   */
  class LIterator {
   private:
    std::shared_ptr<Node<T>> cur;

   public:
    explicit LIterator(std::shared_ptr<Node<T>> obj) : cur(std::move(obj)) {};

    LIterator& operator++() {
      cur = cur->next;
      return *this;
    }

    LIterator operator++(int) {
      LIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    LIterator& operator--() {
      cur = cur->prev;
      return *this;
    }

    LIterator operator--(int) {
      LIterator tmp = *this;
      --(*this);
      return tmp;
    }

    T& operator*() { return cur->data; }
    bool operator==(const LIterator& other) const { return cur == other.cur; }
    bool operator!=(const LIterator& other) const { return cur != other.cur; }
  };

  /**
   * Класс ошибки - список пуст
   */
  class ListEmpty : public std::exception {
   public:
    ListEmpty() { std::cerr << "Список пуст\n"; }
  };

  List() {
    //    this->root = new Node;
    this->root = std::make_shared<Node<T>>();
    this->root->prev = this->root->next = this->root;
    this->root->data = 0;
    this->size = 0;
  };
  attr_MU explicit List(std::shared_ptr<Node<T>> r)
      : root(std::move(r)), size(1){};

  explicit List(std::vector<T> obj) {
    List();
    for (auto& elem : obj) Push_back(elem);
  }

  size_t Size() { return this->size; }

  long GetCount(const std::shared_ptr<Node<T>>&) {
    return this->root.use_count();
  };

  LIterator begin() { return LIterator(this->root->next); }

  LIterator end() { return LIterator(this->root); }

  LIterator rbegin() { return LIterator(this->root->prev); }

  LIterator rend() { return LIterator(this->root); }

  void Print() const {
    //    for (Node* p = this->root->next; p != this->root; p = p->next) {
    //      printf("%d ", p->get_data());
    //    }
    auto p = this->root->next;
    while (p != this->root) {
      printf("%d ", p->get_data());
      p = p->next;
    }
    puts("");
  }

  void Push_back(T obj) {
    //    Node* head = new Node(this->root, obj, this->root->prev);
    auto head = std::make_shared<Node<T>>(this->root, obj, this->root->prev);
    this->root->prev->next = head;
    this->root->prev = head;
    head->next = this->root;
    head->prev = this->root->prev;
    ++this->size;
  }
  /**
   * Вставка после определенной Node
   * @param obj
   * @param it
   */
  void Insert(T obj, const std::shared_ptr<Node<T>>& it) {
    //    Node* new_node = new Node(it->next, obj, it);
    auto new_node = std::make_shared<Node>(it->next, obj, it);
    it->next = new_node;
    it->next->prev = new_node;
    if (new_node->next != NULL) this->root->prev = new_node;
    ++this->size;
  }
  /**
   * Вставка по позиции
   * @param obj
   * @param pos
   */
  void Insert(T obj, size_t pos) {
    if (pos == 0) {
      auto new_node = std::make_shared<Node>(this->root->next, obj, this->root);
      this->root->next = new_node;
      this->root->prev = new_node;
      new_node->next = this->root;
      new_node->prev = this->root;
      ++this->size;
      return;
    }
    auto cur = this->root;
    for (size_t cnt = 0; cnt < pos; ++cnt) {
      cur = cur->next;
    }
    auto new_node = std::make_shared<Node>(cur->next, obj, cur);
    cur->next = new_node;
    new_node->prev = cur;
    if (cur->next != nullptr) {
      cur->next->prev = new_node;
    }
    ++this->size;
  }

  /**
   * Удаление элемента по итератору
   * @param it
   */
  void Remove(const std::shared_ptr<Node<T>>& it) {
    it->prev->next = it->next;
    it->next->prev = it->prev;
    --this->size;
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
  attr_ND std::shared_ptr<Node<T>> l_search(T obj) const {
    auto res = this->root->next;
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
  attr_ND std::shared_ptr<Node<T>> at(size_t ix) const {
    auto cur = this->root;
    for (size_t cnt = 0; cnt < ix + 1; ++cnt) {
      cur = cur->next;
    }
    //    printf("__%d__\n", cur->data);
    return cur;
  }

  /**
   * Удаление элемента по значению
   * @param obj
   */
  void Remove(T obj) {
    auto it = l_search(obj);
    Remove(it);
    --this->size;
  }

  void Destroy() {
    auto cur = this->root->prev;
    while (!this->IsEmpty()) {
      auto tmp = cur;
      Remove(tmp);
      cur = cur->prev->next;
    }
    this->size = 0;
  }

  attr_MU static void swap(const std::shared_ptr<Node<T>>& a,
                           const std::shared_ptr<Node<T>>& b) {
    if (a == b) return;

    auto a_prev = a->prev;
    auto a_next = a->next;
    auto b_prev = b->prev;
    auto b_next = b->next;

    if (a_next == b) {
      auto tmp = b->next;
      a->next = tmp;
      if (tmp != NULL) tmp->prev = a;

      b->next = a;
      b->prev = a_prev;

      a->prev = b;
      if (a_prev != NULL) a_prev->next = b;
    } else if (b_next == a) {
      auto tmp = a->next;
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

  T First() {
    auto first = this->root->next;
    T res = first->get_data();
    return res;
  }

  void Pop_First() {
    if (IsEmpty()) throw ListEmpty();
    auto first = this->root->next;
    first->next->prev = this->root;
    this->root->next = first->next;
    --this->size;
  }

  attr_MU T Last(){
    auto last = this->root->prev;
    return last->get_data();
  }

  attr_MU void PopLast(){
    if (this->IsEmpty()) throw ListEmpty();
    auto last = this->root->prev;
    last->prev->next = this->root;
    this->root->prev = last->prev->next;
    --this->size;

  }

  ~List() { this->Destroy(); }
};

/*
int main() {
  List<int> ll;
  ll.Push_back(22);
  ll.Push_back(2222);
  ll.Push_back(5);

  //  ll.Insert(5, dvatsatdva);
  //  ll.Insert(5, (size_t)2);
  ll.Push_back(4);
  ll.Push_back(8);
  //  Node* dvatsatdva22 = ll.l_search(2222);
  //  Node* dvatsatdva = ll.l_search(4);
  //  ll.Remove(22);
  ll.Print();
  std::cout << '\n';
  auto it_begin = ll.begin();
  auto it_end = ll.end();
  auto it_rend = ll.rend();
  auto it_rbegin = ll.rbegin();
  for (auto it = it_begin; it != it_end; ++it) {
    std::cout << *it << " ";
  }
  std::cout << '\n';
  size_t cnt = 0;
  for (auto it = it_rbegin; it != it_rend && cnt < ll.Size(); --it, ++cnt) {
    std::cout << *it << " ";
  }
  std::cout << '\n';
  //  --it_begin;
  --it_rend;
  std::cout << *(it_rend) << std::endl;  // должно быть 4
  //  printf("%d", ll.search(1)->data);
  //  printf("\t%d\t", ll.IsEmpty());
  //  ll.swap(dvatsatdva, dvatsatdva22);
  //  ll.Print();
  //  ll.Destroy();
  return 0;
}
 */