#include <iostream>
#include <list>

#include "BaseIterator.h"
namespace LList {
template <typename T>
class LIterator final : public BaseIteratorNS::BaseIterator<T> {
 private:
  /// data в BaseIterator

 public:
  LIterator* _next = nullptr;
  LIterator* _prev = nullptr;
  LIterator() = default;
  /**
   * Случай для головы
   * @param data
   */
  explicit LIterator(T data) {
    // this->_data = std::make_shared<T>(data);
    this->PushData(data);
    _next = _prev = nullptr;
  }
  LIterator(T data, LIterator* next, LIterator* prev) {
    this->PushData(data);
    _next = next;
    _prev = prev;
  }

  LIterator* Next() override { return _next; }
  static void next(LIterator<T>*& cur) {
    if (cur != nullptr) {
      cur = cur->_next;
    }
  }
  LIterator* Prev() override { return _prev; }
  static void prev(LIterator<T>*& cur) {
    if (cur != nullptr) {
      cur = cur->_prev;
    }
  }

  T operator*() override { return this->GetData(); }

  LIterator* operator++(int) override {
    LIterator* temp = this;
    if (_next != nullptr) {
      this->_next = _next->_next;
      this->_prev = _next->_prev;
    }
    return temp;
  }

  LIterator* operator--(int) override {
    LIterator* temp = this;
    if (_prev != nullptr) {
      this->_prev = _prev->_prev;
      this->_next = _prev->_next;
    }
    return temp;
  }

  // it = it2 + 5;
  LIterator* operator+(int elem) {
    LIterator* other = this;
    while (elem != 0) {
      other = other->Next();
      if (other == nullptr) throw std::out_of_range("out of range");
      --elem;
    }
    return other;
  }
};

template <typename T>
class LList {
 private:
  LIterator<T>* _head = nullptr;
  LIterator<T>* _tail = nullptr;
  LIterator<T>* _current = nullptr;
  size_t _size = 0;

 public:
  LList() = default;
  ~LList() = default;

  [[nodiscard]] size_t size() const { return _size; }

  LIterator<T>* begin() { return _head; }
  static LIterator<T>* end() { return nullptr; }
  LIterator<T>* rbegin() { return _tail; }
  static LIterator<T>* rend() { return nullptr; }

  void push_back(T obj) {
    if (_size == 0) {
      auto* newobj = new LIterator<T>(obj, nullptr, nullptr);
      _head = _tail = newobj;
    } else {
      auto* newobj = new LIterator<T>(obj, nullptr, _tail);
      _tail->_next = newobj;
      _tail = newobj;
    }
    ++_size;
  }

  T pop_back() {
    T res = _tail->GetData();
    auto* for_del = _tail;
    _tail = _tail->_prev;
    delete for_del;
    return res;
  }

  /**
   *
   * @param index
   * @param obj
   */
  void insert(size_t index, T obj) {
    if (index > _size || index < 0) throw std::out_of_range("Index not found");
    LIterator<T>* cursor = _head;
    while (index != 0LL) {
      cursor = cursor->Next();
      --index;
    }
    auto* newobj = new LIterator<T>(obj, cursor, cursor->Next());
    cursor->_next->_prev = newobj;
    cursor->_next = newobj;
  }
  // void insert(LIterator<T> it, T obj);
};

}  // namespace LList

template <typename T>
void print(LList::LList<T>& ll) {
  // for (auto beg = ll.begin(); beg != ll.end(); ++beg) {
  for (auto it = ll.begin(); it != ll.end(); LList::LIterator<T>::next(it)) {
    std::cout << it->GetData() << ' ';
  }
}

int main() {
  LList::LList<int> ll;
  ll.push_back(5);
  ll.push_back(6);
  ll.push_back(7);
  // auto it = ll.begin();
  // auto ot = it->Next();
  // std::printf("%d", it->GetData());
  // // it = it + 1;
  // it++;
  // std::printf(" %d", it->GetData());
  // std::printf(" %d", ot->GetData());
  // std::cout << ll.pop_back();

  print(ll);

  return 0;
}