#include <assert.h>
#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct T {
  char* word;
  unsigned int count;
} T;

typedef struct Node {
  T data;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

void tree_inline_print(Node* tree) {
  if (tree == NULL) return;
  tree_inline_print(tree->left);
  printf("%s %d\n", tree->data.word, tree->data.count);
  tree_inline_print(tree->right);
}

Node* tree_add(Node* tree, char* obj) {
  if (tree == NULL) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data.word = strdup(obj);
    new_node->left = new_node->right = new_node->parent = NULL;
    new_node->data.count = 1;
    return new_node;
  }
  /**
   * cmp < 0 == obj < data
   * cmp > 0 == obj > data
   */
  int cmp = strcmp(obj, tree->data.word);
  if (cmp < 0) {
    tree->left = tree_add(tree->left, obj);
    if (tree->left != NULL) tree->left->parent = tree;
  } else if (cmp > 0) {
    tree->right = tree_add(tree->right, obj);
    if (tree->right != NULL) tree->right->parent = tree;
  } else {
    tree->data.count++;
  }
  return tree;
}

Node* tree_destroy(Node* tree) {
  if (tree == NULL) return NULL;
  tree_destroy(tree->left);
  tree_destroy(tree->right);
  free(tree->data.word);
  tree->data.count = 0;
  free(tree);
  return NULL;
}

char* stringtolower(char* s) {
  for (int i = 0; s[i] != '\0'; i++) s[i] = tolower(s[i]);
  return s;
}

int tree_node_cnt(Node* tree) {
  if (tree == NULL) return 0;
  int l_n = tree_node_cnt(tree->left);
  int r_n = tree_node_cnt(tree->right);
  return (1 + (l_n + r_n));
}

int cmp(const void* a, const void* b) {
  T* l = *(T**)a;
  T* r = *(T**)b;
  if (l->count > r->count)
    return -1;
  else if (l->count < r->count)
    return 1;
  else {
    return strcmp(l->word, r->word);
  }
}

#define SPECS(c) (c == '-' || c == '\n' || strcmp(&c, "–") == 0 || c == '\0')

char* preprocess(char* str) {
  int N = strlen(str);
  char* res = malloc(sizeof(char) * (N + 1));
  int j = 0;
  for (int i = 0; i < N; ++i) {
    if (isalpha(str[i]) && !SPECS(str[i])) {
      res[j] = str[i];
      ++j;
    }
  }
  res[j] = '\0';
  strcpy(str, res);
  free(res);
  return str;
}

void tree_to_array(Node* tree, T** arr, int* i) {
  if (tree == NULL) return;
  tree_to_array(tree->left, arr, i);
  arr[(*i)++] = &tree->data;
  tree_to_array(tree->right, arr, i);
}

int main() {
  Node* tree = NULL;
  char inpt[1001];
  while (scanf("%1000s", inpt) == 1) {
    stringtolower(inpt);
    preprocess(inpt);
    tree = tree_add(tree, inpt);
  }

  int N = tree_node_cnt(tree);
  T** words = malloc(sizeof(T*) * N);
  int i = 0;
  tree_to_array(tree, words, &i);
  qsort(words, N, sizeof(T*), cmp);
  for (int j = 0; j < N; j++) {
    if (strcmp(words[j]->word, "") == 0) continue;
    printf("%s %d\n", words[j]->word, words[j]->count);
  }
  free(words);
  tree_destroy(tree);
  return 0;
}
