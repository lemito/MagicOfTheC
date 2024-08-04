/**
 * Реализуйте бинарное дерево поиска для целых чисел. Программа получает на вход
 последовательность целых чисел и строит из них дерево. Элементы в деревья
 добавляются в соответствии с результатом поиска их места. Если элемент уже
 существует в дереве, добавлять его не надо. Балансировка дерева не
 производится.

*/
#include <stdio.h>
#include <stdlib.h>

#include "18_ctree_lib.h"

#define MAX(a, b) (a > b ? a : b)

int tree_depth(Node* tree) {
  if (tree == NULL) return 0;
  int l_d = tree_depth(tree->left);
  int r_d = tree_depth(tree->right);
  return MAX(l_d, r_d) + 1;
}

/// можно как-то улучшить, таща высоты в каждой ноде
char tree_is_balanced(Node* tree) {
  if (tree == NULL) return 1;
  int l_d = tree_depth(tree->left);
  int r_d = tree_depth(tree->right);
  if (abs(l_d - r_d) > 1) return 0;
  return (char)(tree_is_balanced(tree->left) == 1 &&
                tree_is_balanced(tree->right) == 1);
}

int main(void) {
  int inpt;
  while (scanf("%d", &inpt) == 1 && inpt != 0) {
    tree = tree_add(tree, inpt);
  }
  printf("%s", tree_is_balanced(tree) == 1 ? "YES" : "NO");
  return 0;
}