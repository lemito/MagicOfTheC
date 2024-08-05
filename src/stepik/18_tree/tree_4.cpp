/**
 * Реализуйте бинарное дерево поиска для целых чисел. Программа получает на вход
 * последовательность целых чисел и строит из них дерево. Элементы в деревья
 * добавляются в соответствии с результатом поиска их места. Если элемент уже
 * существует в дереве, добавлять его не надо. Балансировка дерева не
 * производится.
 */
#include "18_ctree_lib.c"

void tree_inline_print(Node* tree) {
  if (tree == NULL) return;
  if (tree->left == NULL && tree->right == NULL) printf("%d ", tree->data);
  tree_inline_print(tree->left);

  tree_inline_print(tree->right);
}

int main() {
  int inpt;
  while (scanf("%d", &inpt) == 1 && inpt != 0) {
    tree = tree_add(tree, inpt);
  }
  tree_inline_print(tree);
  return 0;
}