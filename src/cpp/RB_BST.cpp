#include "RB_BST.hpp"

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
BST<_Tp, _Alloc, traits_t1>::~BST() {
  _clear(_header);
  _node_count = 0;
}

template <typename _Tp, typename _Alloc, typename traits_t1>
void BST<_Tp, _Alloc, traits_t1>::insert(data_type obj) {
  auto* newNode = new Node<_Tp>(obj);
  _Node_ptr cursor = _header;
  _Node_ptr parent = nullptr;

  while (cursor != nullptr) {
    parent = cursor;
    if (obj < cursor->_data) {
      cursor = cursor->_left;
    } else if (obj > cursor->_data) {
      cursor = cursor->_right;
    } else {
      // std::cerr << "Такой узел уже есть" << std::endl;
      std::cerr << "This node already in use" << std::endl;
      delete newNode;
      return;
    }
  }

  newNode->_parent = parent;
  newNode->_left = newNode->_right = nullptr;

  if (parent == nullptr) {
    newNode->_color = _S_black;
    _header = newNode;
  } else if (obj < parent->_data) {
    parent->_left = newNode;
  } else {
    parent->_right = newNode;
  }

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
typename BST<_Tp, _Alloc, traits_t1>::_TreeIterator
BST<_Tp, _Alloc, traits_t1>::begin() {
  return TreeIterator<_Tp>();
}

template <typename _Tp, typename _Alloc, typename traits_t1>
typename BST<_Tp, _Alloc, traits_t1>::_TreeIterator
BST<_Tp, _Alloc, traits_t1>::end() {
  return TreeIterator<_Tp>();
}
template <typename _Tp, typename _Alloc, typename traits_t1>
void BST<_Tp, _Alloc, traits_t1>::print() {
  if (_header == nullptr)
    std::cerr << "Tree is empty" << std::endl;
  else {
    _print_impl(_header, "", true);
  }
}

template <typename _Tp, typename _Alloc, typename traits_t1>
void BST<_Tp, _Alloc, traits_t1>::_print_impl(_Node_ptr root,
                                              std::string indent, bool last) {
  if (root != nullptr) {
    std::cout << indent;
    if (last) {
      std::cout << "R----";
      indent += "   ";
    } else {
      std::cout << "L----";
      indent += "|  ";
    }
    // std::string sColor = (root->color == RED) ? "RED" : "BLACK";
    std::cout << root->_data << std::endl;
    _print_impl(root->_left, indent, false);
    _print_impl(root->_right, indent, true);
  }
}
template <typename _Tp, typename _Alloc, typename traits_t1>
void BST<_Tp, _Alloc, traits_t1>::_clear(_Node_ptr node) {
  if (node == nullptr) return;

  std::stack<_Node_ptr> st;
  st.push(node);

  while (!st.empty()) {
    _Node_ptr cur = st.top();
    st.pop();

    if (cur->_left != nullptr) st.push(cur->_left);
    if (cur->_right != nullptr) st.push(cur->_right);

    delete cur;
  }
}
}  // namespace bst

int main() {
  std::set<int> smsmsm;
  {
    bst::BST<int> meow;
    smsmsm.insert(52);
    meow.insert(52);
    meow.insert(51);
    meow.insert(53);
    meow.insert(53);
    meow.print();
  }  // тут деструктор для BST
  // auto it = meow.contains(52);
  auto be = smsmsm.begin();
  smsmsm.erase(be);
  return 0;
}