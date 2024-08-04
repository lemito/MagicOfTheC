//
// Created by lemito on 8/4/24.
//

#ifndef MAGICOFTHEC_SRC_STEPIK_18_TREE_18_CTREE_LIB_H_
#define MAGICOFTHEC_SRC_STEPIK_18_TREE_18_CTREE_LIB_H_

#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define BOOL_TO_STR(x) x == true ? "TRUE" : "FALSE"

typedef int T;
typedef struct Node {
  T data;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node* tree = NULL;

void tree_print(Node* tree, size_t level) {
  if (tree == NULL) return;
  tree_print(tree->right, level + 1);
  for (size_t i = 0; i < level; ++i) printf("\t");
  printf("%d\n", tree->data);
  tree_print(tree->left, level + 1);
}

Node* tree_add(Node* tree, T obj) {
  if (tree == NULL) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = obj;
    new_node->left = new_node->right = new_node->parent = NULL;
    return new_node;
  }
  if (obj < tree->data) {
    tree->left = tree_add(tree->left, obj);
    tree->left->parent = tree;
  }
  if (obj > tree->data) {
    tree->right = tree_add(tree->right, obj);
    tree->right->parent = tree;
  }
  return tree;
}

Node* tree_search(Node* tree, T obj) {
  do {
    if (obj < tree->data) tree = tree->left;
    if (obj > tree->data) tree = tree->right;
    if (tree->data == obj) {
      return tree;
    }
  } while (tree->left != NULL && tree->right != NULL);
  return NULL;
}

Node* tree_destroy(Node* tree) {
  if (tree == NULL) return NULL;
  tree_destroy(tree->left);
  tree_destroy(tree->right);
  free(tree);
  return NULL;
}

Node* tree_delete(Node* tree, T obj) {
  if (tree == NULL) return NULL;
  Node* work = tree_search(tree, obj);
  if (work == NULL) return tree;
  if (work->left == NULL && work->right == NULL) {  // лист
    if (work->parent->left == work)
      work->parent->left = NULL;
    else
      work->parent->right = NULL;
    free(work);
    work = NULL;
  } else if (work->left == NULL || work->right == NULL) {  // 1 потомок
    if (work->parent->right == work) {
      if (work->right != NULL) {
        work->parent->right = work->right;
      } else if (work->left != NULL) {
        work->parent->right = work->left;
      }
    } else {
      if (work->right != NULL) {
        work->parent->left = work->right;
      } else if (work->left != NULL) {
        work->parent->left = work->left;
      }
    }
    free(work);
    work = NULL;
  } else {  // 2 потомка
    Node* tmp = work->right;
    while (tmp->left != NULL) {
      tmp = tmp->left;
    }
    work->data = tmp->data;
    if (tmp->parent->left == tmp) {
      tmp->parent->left = tmp->right;
    } else {
      tmp->parent->right = tmp->right;
    }
    if (tmp->right != NULL) {
      tmp->right->parent = tmp->parent;
    }
    free(tmp);
    work = NULL;
  }
  return tree;
}

#endif  // MAGICOFTHEC_SRC_STEPIK_18_TREE_18_CTREE_LIB_H_
