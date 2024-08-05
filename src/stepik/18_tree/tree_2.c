/**
 * Распечатайте последовательность натуральных чисел по возрастанию, печатая
 * каждое число один раз. Для решения задачи используйте бинарное дерево.
 */
#include <stdio.h>

#include "18_ctree_lib.c"

void tree_inline_print(Node* tree) {
  if (tree == NULL) return;
  tree_inline_print(tree->left);
  printf("%d ", tree->data);
  tree_inline_print(tree->right);
}

int main(void) {
  int inpt;
  while (scanf("%d", &inpt) == 1 && inpt != 0) {
    tree = tree_add(tree, inpt);
  }
  tree_inline_print(tree);
  return 0;
}