/**
 * Реализуйте бинарное дерево поиска для целых чисел. Программа получает на вход
 последовательность целых чисел и строит из них дерево. Элементы в деревья
 добавляются в соответствии с результатом поиска их места. Если элемент уже
 существует в дереве, добавлять его не надо. Балансировка дерева не
 производится.
*/
#include <stdio.h>
#include <stdlib.h>

#include "18_ctree_lib.c"

#define MAX(a, b) (a > b ? a : b)

int tree_depth(Node* tree) {
  if (tree == NULL) return 0;
  int l_d = tree_depth(tree->left);
  int r_d = tree_depth(tree->right);
  return MAX(l_d, r_d) + 1;
}

void print_lvl(Node* node, int N, int lvl) {
  if (node == NULL) return;
  if (lvl == N) printf("%d ", node->data);
  print_lvl(node->left, N, lvl + 1);
  print_lvl(node->right, N, lvl + 1);
}

int main(void) {
  int inpt;
  int N;
  while (scanf("%d", &inpt) == 1 && inpt != 0) {
    tree = tree_add(tree, inpt);
  }
  scanf("%d", &N);
  print_lvl(tree, N, 0);

  return 0;
}