#pragma once

#include <memory>

namespace BaseIteratorNS {
template <typename T>
class BaseIterator {
 public:
  BaseIterator() = default;
  virtual ~BaseIterator() = default;

  bool operator==(const BaseIterator &other) const {
    return _data.get() == other._data.get();
  }

  bool operator!=(const BaseIterator &other) const { return !(*this == other); }

  virtual T &operator*();
  virtual const T &operator*() const;

  virtual BaseIterator *Next();
  virtual BaseIterator *Prev();

  virtual BaseIterator *operator++() { return nullptr; }
  virtual BaseIterator *operator++(int) { return nullptr; }
  virtual BaseIterator *operator--() { return nullptr; }
  virtual BaseIterator *operator--(int) { return nullptr; }

  void PushData(T obj);
  T GetData();

 protected:
  std::shared_ptr<T> _data = std::make_shared<T>();
};
//
// template <typename T>
// inline bool BaseIterator<T>::operator==(const BaseIterator &other) {
//   return (*this == other);
// }
//
// template <typename T>
// inline bool BaseIterator<T>::operator!=(const BaseIterator &other) {
//   return (*this == other);
// }

template <typename T>
inline T &BaseIterator<T>::operator*() {
  return *_data;
}

template <typename T>
inline const T &BaseIterator<T>::operator*() const {
  return *_data;
}

template <typename T>
inline BaseIterator<T> *BaseIterator<T>::Next() {
  return nullptr;
}

template <typename T>
inline BaseIterator<T> *BaseIterator<T>::Prev() {
  return nullptr;
}
//
// template <typename T>
// inline BaseIterator<T>* BaseIterator<T>::GetCur() {
//   return this->__current;
// }
template <typename T>
inline void BaseIterator<T>::PushData(T obj) {
  _data = std::make_shared<T>(obj);
}
template <typename T>
inline T BaseIterator<T>::GetData() {
  return *(_data);
}
}  // namespace BaseIteratorNS