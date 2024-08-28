#include "BST.hpp"

#include <iostream>
#include <set>

namespace bst {
template <typename _Tp>
void TreeIterator<_Tp>::parent() {
  this->cur = this->cur->_parent;
}

template <typename _Tp>
void TreeIterator<_Tp>::left() {
  this->cur = this->cur->_left;
}

template <typename _Tp>
void TreeIterator<_Tp>::right() {
  this->cur = this->cur->_right;
}

template <typename _Tp, typename _Alloc, typename traits_t1>
void BST<_Tp, _Alloc, traits_t1>::insert(data_type obj) {
  if (this->_node_count == 0) {
    _header = new Node<_Tp>(obj);
    ++_node_count;
    return;
  }

  auto* newNode = new Node<_Tp>(obj);
  _Node_ptr cursor = _header;
  _Node_ptr parent = nullptr;
  while (cursor != nullptr) {
    data_type cur_data = cursor->_data;
    parent = cursor;
    if (obj < cur_data) {
      cursor = cursor->_left;
    } else if (obj > cur_data) {
      cursor = cursor->_right;
    } else {
      std::cerr << "Такой узел уже есть" << std::endl;
      return;
    }
  }
  newNode->_parent = parent;
  newNode->_left = newNode->_right = nullptr;

  if (obj < parent->_data)
    parent->_left = newNode;
  else
    parent->_right = newNode;
  ++_node_count;
}

template <typename _Tp, typename _Alloc, typename traits_t1>
void BST<_Tp, _Alloc, traits_t1>::remove(data_type obj) {}

template <typename _Tp, typename _Alloc, typename traits_t1>
typename BST<_Tp, _Alloc, traits_t1>::data_type
BST<_Tp, _Alloc, traits_t1>::minimum() {}

template <typename _Tp, typename _Alloc, typename traits_t1>
typename BST<_Tp, _Alloc, traits_t1>::data_type
BST<_Tp, _Alloc, traits_t1>::maximum() {}

template <typename _Tp, typename _Alloc, typename traits_t1>
size_t BST<_Tp, _Alloc, traits_t1>::node_count() const {
  return _node_count;
}

template <typename _Tp, typename _Alloc, typename traits_t1>
typename BST<_Tp, _Alloc, traits_t1>::_TreeIterator_ptr
BST<_Tp, _Alloc, traits_t1>::search(data_type obj) {
  _Node_ptr cursor = _header;
  while (cursor != nullptr) {
    data_type cur_data = cursor->_data;
    if (obj == cur_data) {
      _TreeIterator pre_res = _TreeIterator(cursor);
      _TreeIterator_ptr res = &pre_res;
      return res;
    }
    if (obj < cur_data) {
      cursor = cursor->_left;
    } else if (obj > cur_data) {
      cursor = cursor->_right;
    }
  }
  return nullptr;
}
template <typename _Tp, typename _Alloc, typename traits_t1>
bool BST<_Tp, _Alloc, traits_t1>::contains(data_type obj) {
  if (search(obj) != nullptr) return true;
  return false;
}

template <typename _Tp, typename _Alloc, typename traits_t1>
void BST<_Tp, _Alloc, traits_t1>::LRR() {}
}  // namespace bst

int main() {
  std::set<int> smsmsm;
  bst::BST<int> meow;
  smsmsm.insert(78);
  meow.insert(52);
  meow.insert(51);
  meow.insert(53);
  // auto it = meow.contains(52);

  return 0;
}