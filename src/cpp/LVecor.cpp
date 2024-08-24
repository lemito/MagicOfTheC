#include <iostream>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#include "BaseIterator.h"
namespace LVector {
template <typename T>
class LVectorIterator final : public BaseIteratorNS::BaseIterator<T> {
 public:
  explicit LVectorIterator(T* data) : _data(data) {}
  ~LVectorIterator() override = default;

  LVectorIterator* Next() override;
  LVectorIterator* Prev() override;

  T& operator*() override;
  const T& operator*() const override;

  LVectorIterator* operator++() override;
  LVectorIterator* operator++(int) override;
  LVectorIterator* operator--() override;
  LVectorIterator* operator--(int) override;

  bool operator==(const LVectorIterator& other) const;
  bool operator!=(const LVectorIterator& other) const;

 private:
  T* _data;
};

// template <typename T>
// LVectorIterator<T>::~LVectorIterator() {
//   delete _data;
// }

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::Next() {
  return new LVectorIterator<T>(_data + 1);
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::Prev() {
  return new LVectorIterator<T>(_data - 1);
}

template <typename T>
inline T& LVectorIterator<T>::operator*() {
  return *_data;
}

template <typename T>
inline const T& LVectorIterator<T>::operator*() const {
  return *_data;
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::operator++() {
  ++_data;
  return this;
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::operator++(int) {
  LVectorIterator* tmp = new LVectorIterator<T>(_data);
  ++_data;
  return tmp;
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::operator--() {
  --_data;
  return this;
}

template <typename T>
LVectorIterator<T>* LVectorIterator<T>::operator--(int) {
  LVectorIterator<T>* tmp = new LVectorIterator<T>(_data);
  --_data;
  return tmp;
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
  LVector() : _size(0), _capacity(1) { _data = new T[_capacity]; }
  ~LVector() { delete[] _data; }

  void push_back(T obj);

  size_t size();

  T operator[](size_t index) const { return _data[index]; }

  LVectorIterator<T> begin() const { return LVectorIterator<T>(_data); }
  LVectorIterator<T> end() const { return LVectorIterator<T>(_data + _size); }

 private:
  size_t _size;
  size_t _capacity;
  T* _data;

  /**
   * Возвращает новый массив данных с больших/меньшим кол-вом памяти
   * @param new_size
   * @return
   */
  T* _resize(const size_t new_size) {
    T* new_data = new T[new_size];
    // std::copy(_data, _data +  MIN(_size, new_size), new_data);
    memmove(new_data, _data, MAX(_capacity, _size));
    // _size = new_size;
    return new_data;
  }
};

template <typename T>
void LVector<T>::push_back(T obj) {
  _data[_size] = obj;
  ++_size;
  if (_capacity <= _size) {
    _capacity += 10;
    _data = _resize(_capacity);
  }
}
template <typename T>
size_t LVector<T>::size() {
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

void Printer_by_it(LVector::LVector<int>& ll) {
  for (auto it = ll.begin(); it != ll.end(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';
}

int main() {
  LVector::LVector<int> ll{};
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(5);
  // Printer_by_ix(ll);
  Printer_by_it(ll);
  return 0;
}