/**
 * Бинарное дерево на C++
 *
 *
 * TODO: можно пойти дальше и сделать его версию AVL или Red&Black
 */
#include <iostream>
#include <ostream>

#define attr_ND [[nodiscard]]
#ifdef NULL
#define NULL nullptr
#endif

template <typename T>
class BinIt {
 private:
  T data;
  BinIt* parent;
  BinIt* left;
  BinIt* right;

 public:
  BinIt() = default;
  explicit BinIt(T data)
      : data(data), parent(nullptr), left(nullptr), right(nullptr) {};
  void SetData(T obj) { this->data = obj; }
  attr_ND T GetData() const { return this->data; }
  attr_ND BinIt* Left() const { return this->left; }
  attr_ND BinIt* Right() const { return this->right; }
  attr_ND BinIt* Parent() const { return this->parent; }
  void SetLeft(BinIt* node) { this->left = node; }
  void SetRight(BinIt* node) { this->right = node; }
  void SetParent(BinIt* node) { this->parent = node; }
};

template <typename T>
class BinTree {
 private:
  BinIt<T>* root;

  void _print(BinIt<T>* node, std::ostream& os, size_t level) {
    if (node != nullptr) {
      _print(node->Right(), os, level + 1);
      for (size_t i = 0; i < level; ++i) printf("\t");
      os << node->GetData() << '\n';
      _print(node->Left(), os, level + 1);
      ++level;
    }
  }

  void _insert(BinIt<T>* node, T obj) {
    while (true) {
      if (obj < node->GetData()) {
        if (node->Left() == nullptr) {
          node->SetLeft(new BinIt<T>(obj));
          node->Left()->SetParent(node);
          break;
        } else {
          node = node->Left();
        }
      } else {
        if (node->Right() == nullptr) {
          node->SetRight(new BinIt<T>(obj));
          node->Right()->SetParent(node);
          break;
        } else {
          node = node->Right();
        }
      }
    }
  }

  BinIt<T>* _search(BinIt<T>* node, T obj) {
    while (node != NULL) {
      if (obj < node->GetData()) node = node->Left();
      if (obj > node->GetData()) node = node->Right();
      if (obj == node->GetData()) return node;
    }
    return NULL;
  }

  void _remove(BinIt<T>* node) {
    // лист
    if (node->Left() == NULL || node->Right() == NULL) {
      if (node->Parent()->Left() == node)
        node->Parent()->SetLeft(NULL);
      else
        node->Parent()->SetRight(NULL);
      delete node;
      node = NULL;
      return;
    } else if (node->Left() == NULL || node->Right() == NULL) {  // 1 потомок
      if (node->Parent()->Right() == node) {
        if (node->Right() != NULL) {
          node->Parent()->SetRight(node->Right());
        } else if (node->Left() != NULL) {
          node->Parent()->SetRight(node->Left());
        }
      } else {
        if (node->Right() != NULL) {
          node->Parent()->SetLeft(node->Right());
        } else if (node->Left() != NULL) {
          node->Parent()->SetLeft(node->Left());
        }
      }
      delete node;
      node = NULL;
      return;
    } else {  // 2 потомка
      auto* tmp = node->Right();
      while (tmp->Left() != NULL) {
        tmp = tmp->Left();
      }
      node->SetData(tmp->GetData());
      if (tmp->Parent()->Left() == tmp) {
        tmp->Parent()->SetLeft(tmp->Right());
      } else {
        tmp->Parent()->SetRight(tmp->Right());
      }
      if (tmp->Right() != NULL) {
        tmp->Right()->SetParent(tmp->Parent());
      }
      delete tmp;
      node = NULL;
      return;
    }
  }

 public:
  BinTree() : root(nullptr) {};
  void insert(T obj) {
    if (this->root == nullptr) {
      auto* node = new BinIt<T>(obj);
      this->root = node;
      return;
    } else {
      _insert(this->root, obj);
    }
  }

  void print(std::ostream& os) {
    _print(this->root, os, 0);
    std::cout << '\n';
  }

  bool contains(T obj) { return _search(this->root, obj) != nullptr; }

  void remove(T obj) {
    if (!contains(obj)) return;
    auto* work = _search(this->root, obj);
    _remove(work);
  }

  friend std::ostream& operator<<(std::ostream& os, BinTree<T>& tree) {
    tree.print(os);
    return os;
  }
};

int main() {
  BinTree<int> tr{};
  tr.insert(10);
  tr.insert(5);
  tr.insert(15);
  tr.insert(1);
  tr.insert(7);
  tr.insert(14);
  tr.insert(20);
  //  tr.print(std::cout);
  std::cout << tr;
  //  bool f1 = tr.contains(14);
  //  std::cout << '\n';
  //  bool f2 = tr.contains(52);
  //  std::cout << f1 << ' ' << f2;
  tr.remove(5);
  std::cout << '\n';
  std::cout << tr;
  return 0;
}