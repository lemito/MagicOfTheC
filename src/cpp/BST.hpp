#ifndef BST_HPP
#define BST_HPP

#include <memory>

namespace bst {

template <typename _Tp, typename _Alloc = std::allocator<_Tp>,
          typename traits_t1 = std::allocator_traits<_Alloc> >
struct Node {
  typedef _Alloc alloc_object;  // объект аллокатара
  typedef _Tp data_type;        // тип хранимого значения
  typedef _Tp& data_ref;        // ссылочный тип к типу
  typedef _Tp* data_ptr;        // хранилище (кусочек памяти)
  typedef Node _Self;           // объект узла
  typedef Node* _Self_ptr;      // указатель на узел
  typedef Node& _Self_ref;      // ссылочный тип на узел

  _Self_ptr _parent = nullptr;
  _Self_ptr _left = nullptr;
  _Self_ptr _right = nullptr;

  _Tp _data;

  /**
   *
   */
  Node() = default;
  /**
   *
   * @param data
   */
  explicit Node(_Tp data)
      : _parent(nullptr), _left(nullptr), _right(nullptr), _data(data) {}
  /**
   *
   * @param data
   * @param left
   * @param right
   * @param parent
   */
  Node(_Tp data, _Self_ptr left, _Self_ptr right, _Self_ptr parent)
      : _parent(parent), _left(left), _right(right), _data(data) {}
  ~Node() = default;
};

template <typename _Tp>
struct TreeIterator {
  typedef _Tp data_type;            // тип хранимого значения
  typedef _Tp& data_ref;            // ссылочный тип к типу
  typedef _Tp* data_ptr;            // хранилище (кусочек памяти)
  typedef Node<_Tp> _Node;          // объект узла
  typedef Node<_Tp>* _Node_ptr;     // указатель на узел
  typedef Node<_Tp>& _Node_ref;     // ссылочный тип на узел
  typedef TreeIterator _Self;       // объект итератор
  typedef TreeIterator* _Self_ptr;  // указатель на итератор
  typedef TreeIterator& _Self_ref;  // ссылочный тип на итератор

  _Node_ptr cur = nullptr;

  TreeIterator() = default;
  explicit TreeIterator(_Node_ptr current) : cur(current) {}
  ~TreeIterator() = default;

  void parent();
  void left();
  void right();
};

template <typename _Tp, typename _Alloc = std::allocator<_Tp>,
          typename traits_t1 = std::allocator_traits<_Alloc> >
class BST {
  typedef _Alloc alloc_object;                   // объект аллокатара
  typedef _Tp data_type;                         // тип хранимого значения
  typedef _Tp& data_ref;                         // ссылочный тип к типу
  typedef _Tp* data_ptr;                         // хранилище (кусочек памяти)
  typedef TreeIterator<_Tp> _TreeIterator;       // объект итератор
  typedef TreeIterator<_Tp>* _TreeIterator_ptr;  // указатель на итератор
  typedef TreeIterator<_Tp>& _TreeIterator_ref;  // ссылочный тип на итератор
  typedef Node<_Tp> _Node;                       // объект узла
  typedef Node<_Tp>* _Node_ptr;                  // указатель на узел
  typedef Node<_Tp>& _Node_ref;                  // ссылочный тип на узел

  _Node_ptr _header = nullptr;  // root
  size_t _node_count = 0;       // количество узлов

 public:
  void insert(data_type obj);
  void remove(data_type obj);
  data_type minimum();
  data_type maximum();
  [[nodiscard]] size_t node_count() const;
  _TreeIterator_ptr search(data_type obj);

  /**
   * ЛКП
   */
  void LRR();
};

}  // namespace bst

#endif  // BST_HPP
