#include <iostream>
#include <typeinfo>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define TERMINATOR_PTR nullptr

#define RESIZE(ptr, new_size) (_new_ptr = )

#include "BaseIterator.h"
namespace LVector {
template <typename T>
class LVectorIterator final : public BaseIteratorNS::BaseIterator<T> {
 public:
  LVectorIterator() = default;
  explicit LVectorIterator(T data, const size_t ix) : _ix(ix), _data(data) {}
  ~LVectorIterator() override = default;

  LVectorIterator* Next() override;
  LVectorIterator* Prev() override;

  T& operator*() override;
  const T& operator*() const override;

  LVectorIterator* operator++() override;
  LVectorIterator* operator++(int) override;
  LVectorIterator* operator--() override;
  LVectorIterator* operator--(int) override;

  // LVectorIterator& operator=();

  bool operator==(const LVectorIterator& other) const;
  bool operator!=(const LVectorIterator& other) const;

  T data() { return _data; }
  void set_data(T obj) { _data = obj; }

  size_t ix() { return _ix; }
  void set_ix(size_t ix) { _ix = ix; }

 private:
  size_t _ix = 0;
  T _data = 0;
  LVectorIterator* _next = TERMINATOR_PTR;
  LVectorIterator* _prev = TERMINATOR_PTR;
};

// template <typename T>
// LVectorIterator<T>::~LVectorIterator() {
//   delete[] _data;
// }

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::Next() {
  return _next;
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::Prev() {
  return _prev;
}

template <typename T>
inline T& LVectorIterator<T>::operator*() {
  return _data;
}

template <typename T>
inline const T& LVectorIterator<T>::operator*() const {
  return _data;
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::operator++() {
  _ix++;
  return _next;
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::operator++(int) {
  ++_ix;
  return _next;
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::operator--() {
  _ix--;
  return _prev;
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::operator--(int) {
  --_ix;
  return _prev;
}

template <typename T>
bool LVectorIterator<T>::operator==(const LVectorIterator& other) const {
  return _data == other._data;
}

template <typename T>
bool LVectorIterator<T>::operator!=(const LVectorIterator& other) const {
  return !(*this == other);
}

template <typename T>
class LVector {
 public:
  LVector() : _size(0), _capacity(1) {
    _data = new LVectorIterator<T>[_capacity];
  }
  ~LVector() { delete[] _data; }

  void push_back(T obj);

  const size_t size() const;

  T operator[](size_t index) {
    if (index > _size) throw std::out_of_range("Index not found");
    return _data[index].data();
  }

  T operator[](size_t index) const {
    if (index > _size) throw std::out_of_range("Index not found");
    return _data[index].data();
  }

  T at(size_t index) const { return this[index]; }

  LVectorIterator<T> begin() const { return _data[0]; }
  LVectorIterator<T> end() const { return _data[_size - 1]; }

 private:
  size_t _size;      // размер
  size_t _capacity;  // капасити :)
  // T* _data;
  LVectorIterator<T>* _data;  // массив итераторов

  /**
   * Возвращает новый массив данных с больших/меньшим кол-вом памяти
   * @param new_size
   * @return
   */
  LVectorIterator<T>* _resize(const size_t new_size) {
    auto* new_data = new LVectorIterator<T>[new_size];
    memcpy(new_data, _data, _size * sizeof(LVectorIterator<T>));
    delete[] _data;
    return new_data;
  }
};

template <typename T>
void LVector<T>::push_back(T obj) {
  _data[_size].set_data(obj);
  _data[_size].set_ix(_size);
  ++_size;
  if (_capacity <= _size) {
    _capacity += 10;
    _data = _resize(_capacity);
  }
}

template <typename T>
const size_t LVector<T>::size() const {
  return this->_size;
}

}  // namespace LVector

void Printer_by_ix(LVector::LVector<int>& ll) {
  const size_t ss = ll.size();
  for (size_t i = 0; i < ss; ++i) {
    std::cout << ll[i] << ' ';
  }
  std::cout << '\n';
}

// todo: доработать итераторы
void Printer_by_it(LVector::LVector<int>& ll) {
  // auto bb = ll.begin();
  // auto ee = ll.end();
  // std::cout << bb.data() << ' ' << ee.data();
  auto it = ll.begin();
  for (; it != ll.end(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';
}

int main() {
  LVector::LVector<int> ll{};
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(5);
  Printer_by_ix(ll);
  // Printer_by_it(ll);
  // try {
  //   const int error = ll[10];
  //   std::cout << error << std::endl;
  // } catch (std::exception& e) {
  //   std::cerr << e.what();
  // }
  return 0;
}