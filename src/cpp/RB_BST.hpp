#ifndef BST_HPP
#define BST_HPP

/**
 * @brief Ошибка. Текст пишется красным цветом
 *
 */
#define ERROR(format, ...) printf("\033[1;31m%s\033[0m\n", text)
/**
 * @brief Предупреждение. Текст пишется жёлтым цветом
 *
 */
#define WARNING(text) printf("\033[1;33m%s\033[0m\n", text)
/**
 * @brief Успешное выполнение чего-либо, логирование. Текст пишется зелёным
 * цветом
 *
 */
#define SUCCESS(text) printf("\033[1;32m%s\033[0m\n", text)

#include <bits/stl_tree.h>

#include <memory>
#include <stack>

namespace bst {
enum _Rb_tree_color { _S_red = false, _S_black = true };

template <typename _Tp, typename _Alloc = std::allocator<_Tp>,
          typename traits_t1 = std::allocator_traits<_Alloc> >
struct Node {
  typedef _Alloc alloc_object;  // объект аллокатара
  typedef _Tp data_type;        // тип хранимого значения
  typedef _Tp& data_ref;        // ссылочный тип к типу
  typedef _Tp* data_ptr;    // хранилище (кусочек памяти)
  typedef Node _Self;       // объект узла
  typedef Node* _Self_ptr;  // указатель на узел
  typedef Node& _Self_ref;  // ссылочный тип на узел
  typedef _Rb_tree_color _Node_color;  // вдруг захочу сделать RB дерево

  _Self_ptr _parent = nullptr;
  _Self_ptr _left = nullptr;
  _Self_ptr _right = nullptr;

  _Tp _data;

  _Node_color _color = _S_red;

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

  /** часть для балансировки */
  void rotateLeft(_Self_ptr cur);
  void rotateRight(_Self_ptr cur);
  void insert_rebalance(_Self_ptr obj);
  void remove_rebalance(_Self_ptr obj);
  /** ====================== */
};

template <typename _Tp>
struct TreeIterator {
  typedef _Tp data_type;    // тип хранимого значения
  typedef _Tp& data_ref;    // ссылочный тип к типу
  typedef _Tp* data_ptr;    // хранилище (кусочек памяти)
  typedef Node<_Tp> _Node;  // объект узла
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
// todo: Доделаю потом, а может и нет
class BST {
  typedef _Alloc alloc_object;  // объект аллокатара
  typedef _Tp data_type;        // тип хранимого значения
  typedef _Tp& data_ref;        // ссылочный тип к типу
  typedef _Tp* data_ptr;  // хранилище (кусочек памяти)
  typedef TreeIterator<_Tp> _TreeIterator;  // объект итератор
  typedef TreeIterator<_Tp>* _TreeIterator_ptr;  // указатель на итератор
  typedef TreeIterator<_Tp>& _TreeIterator_ref;  // ссылочный тип на итератор
  typedef Node<_Tp> _Node;                       // объект узла
  typedef Node<_Tp>* _Node_ptr;  // указатель на узел
  typedef Node<_Tp>& _Node_ref;  // ссылочный тип на узел

  _Node_ptr _header = nullptr;  // root
  size_t _node_count = 0;       // количество узлов

 public:
  BST() = default;
  ~BST();

  void insert(data_type obj);
  void remove(data_type obj);
  data_type minimum();
  data_type maximum();
  [[nodiscard]] size_t node_count() const;
  _TreeIterator_ptr search(data_type obj);
  bool contains(data_type obj);

  virtual _TreeIterator begin();
  virtual _TreeIterator end();

  void print();

 private:
  void _print_impl(_Node_ptr root, std::string indent, bool last);
  void _clear(_Node_ptr node);
};
}  // namespace bst

#endif  // BST_HPP
