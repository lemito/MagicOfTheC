/**
 * Сделано GPT4o в развлекательных и ознакомительных целях
 * Может содержать ошибки и не точности
 * И еще я не автор
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG(fmt, ...)         \
  {                           \
    printf(fmt, __VA_ARGS__); \
    fflush(stdout);           \
  }

#define ORDER 3  // B+ tree order (number of children)

typedef struct Node {
  int keys[ORDER - 1];           // Array of keys
  struct Node *children[ORDER];  // Array of child pointers
  struct Node *next;             // Pointer to next leaf for linked leaf nodes
  int numKeys;                   // Number of keys
  int isLeaf;                    // Boolean flag for leaf node
} Node;

// Function to create a new node
Node *createNode(int isLeaf) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->numKeys = 0;
  newNode->isLeaf = isLeaf;
  for (int i = 0; i < ORDER; i++) {
    newNode->children[i] = NULL;
  }
  newNode->next = NULL;
  return newNode;
}

// Function to split a full node during insertion
void splitChild(Node *parent, int i, Node *child) {
  Node *newChild = createNode(child->isLeaf);
  newChild->numKeys = ORDER / 2;

  for (int j = 0; j < ORDER / 2; j++) {
    newChild->keys[j] = child->keys[j + ORDER / 2];
  }

  if (!child->isLeaf) {
    for (int j = 0; j < ORDER / 2 + 1; j++) {
      newChild->children[j] = child->children[j + ORDER / 2];
    }
  }

  child->numKeys = ORDER / 2;

  for (int j = parent->numKeys; j >= i + 1; j--) {
    parent->children[j + 1] = parent->children[j];
  }

  parent->children[i + 1] = newChild;

  for (int j = parent->numKeys - 1; j >= i; j--) {
    parent->keys[j + 1] = parent->keys[j];
  }

  parent->keys[i] = child->keys[ORDER / 2];
  parent->numKeys++;
}

// Function to insert a key into a non-full node
void insertNonFull(Node *node, int key) {
  int i = node->numKeys - 1;

  if (node->isLeaf) {
    while (i >= 0 && node->keys[i] > key) {
      node->keys[i + 1] = node->keys[i];
      i--;
    }
    node->keys[i + 1] = key;
    node->numKeys++;
  } else {
    while (i >= 0 && node->keys[i] > key) {
      i--;
    }
    i++;
    if (node->children[i]->numKeys == ORDER - 1) {
      splitChild(node, i, node->children[i]);
      if (node->keys[i] < key) {
        i++;
      }
    }
    insertNonFull(node->children[i], key);
  }
}

// Function to insert a key into the B+ tree
void insert(Node **root, int key) {
  if (*root == NULL) {
    *root = createNode(1);
    (*root)->keys[0] = key;
    (*root)->numKeys = 1;
  } else {
    if ((*root)->numKeys == ORDER - 1) {
      Node *newRoot = createNode(0);
      newRoot->children[0] = *root;
      splitChild(newRoot, 0, *root);

      int i = 0;
      if (newRoot->keys[0] < key) {
        i++;
      }
      insertNonFull(newRoot->children[i], key);
      *root = newRoot;
    } else {
      insertNonFull(*root, key);
    }
  }
}

// Function to merge nodes during deletion
void merge(Node *parent, int idx) {
  Node *leftChild = parent->children[idx];
  Node *rightChild = parent->children[idx + 1];

  leftChild->keys[leftChild->numKeys] = parent->keys[idx];

  for (int i = 0; i < rightChild->numKeys; i++) {
    leftChild->keys[leftChild->numKeys + 1 + i] = rightChild->keys[i];
  }

  if (!leftChild->isLeaf) {
    for (int i = 0; i <= rightChild->numKeys; i++) {
      leftChild->children[leftChild->numKeys + 1 + i] = rightChild->children[i];
    }
  }

  for (int i = idx + 1; i < parent->numKeys; i++) {
    parent->keys[i - 1] = parent->keys[i];
  }

  for (int i = idx + 2; i <= parent->numKeys; i++) {
    parent->children[i - 1] = parent->children[i];
  }

  leftChild->numKeys += rightChild->numKeys + 1;
  parent->numKeys--;

  free(rightChild);
}

// A function to find the key's predecessor
Node *findPredecessor(Node *node) {
  while (!node->isLeaf) {
    node = node->children[node->numKeys];
  }
  return node;
}

// A function to find the key's successor
Node *findSuccessor(Node *node) {
  while (!node->isLeaf) {
    node = node->children[0];
  }
  return node;
}

// A function to fill a child node during deletion
void fill(Node *parent, int idx) {
  if (idx != 0 && parent->children[idx - 1]->numKeys >= ORDER / 2) {
    // Borrow from previous
    Node *child = parent->children[idx];
    Node *sibling = parent->children[idx - 1];

    for (int i = child->numKeys - 1; i >= 0; --i) {
      child->keys[i + 1] = child->keys[i];
    }

    if (!child->isLeaf) {
      for (int i = child->numKeys; i >= 0; --i) {
        child->children[i + 1] = child->children[i];
      }
    }

    child->keys[0] = parent->keys[idx - 1];

    if (!parent->isLeaf) {
      child->children[0] = sibling->children[sibling->numKeys];
    }

    parent->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];
    child->numKeys += 1;
    sibling->numKeys -= 1;
  } else if (idx != parent->numKeys &&
             parent->children[idx + 1]->numKeys >= ORDER / 2) {
    // Borrow from next
    Node *child = parent->children[idx];
    Node *sibling = parent->children[idx + 1];

    child->keys[child->numKeys] = parent->keys[idx];

    if (!(child->isLeaf)) {
      child->children[child->numKeys + 1] = sibling->children[0];
    }

    parent->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->numKeys; ++i) {
      sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->isLeaf) {
      for (int i = 1; i <= sibling->numKeys; ++i) {
        sibling->children[i - 1] = sibling->children[i];
      }
    }

    child->numKeys += 1;
    sibling->numKeys -= 1;
  } else {
    // Merge
    if (idx != parent->numKeys) {
      merge(parent, idx);
    } else {
      merge(parent, idx - 1);
    }
  }
}

// A recursive function to delete key in subtree rooted with node
void deleteNode(Node *node, int key) {
  int idx = 0;
  while (idx < node->numKeys && node->keys[idx] < key) {
    ++idx;
  }

  if (idx < node->numKeys && node->keys[idx] == key) {
    if (node->isLeaf) {
      // Key is in leaf
      for (int i = idx + 1; i < node->numKeys; ++i) {
        node->keys[i - 1] = node->keys[i];
      }
      node->numKeys--;
    } else {
      // Key is in internal node
      if (node->children[idx]->numKeys >= ORDER / 2) {
        Node *pred = findPredecessor(node->children[idx]);
        int predKey = pred->keys[pred->numKeys - 1];
        node->keys[idx] = predKey;
        deleteNode(node->children[idx], predKey);
      } else if (node->children[idx + 1]->numKeys >= ORDER / 2) {
        Node *succ = findSuccessor(node->children[idx + 1]);
        int succKey = succ->keys[0];
        node->keys[idx] = succKey;
        deleteNode(node->children[idx + 1], succKey);
      } else {
        merge(node, idx);
        deleteNode(node->children[idx], key);
      }
    }
  } else {
    // Key is not present, delete from appropriate child
    if (node->isLeaf) {
      // Key is not present in tree
      return;
    }

    bool flag = (idx == node->numKeys);

    if (node->children[idx]->numKeys < ORDER / 2) {
      fill(node, idx);
    }

    if (flag && idx > node->numKeys) {
      deleteNode(node->children[idx - 1], key);
    } else {
      deleteNode(node->children[idx], key);
    }
  }

  if (node->isLeaf) {
    return;
  }

  if (node->numKeys >= ORDER / 2) {
    return;
  }

  if (idx == 0) {
    if (node->children[1]->numKeys >= ORDER / 2) {
      fill(node, 1);
    } else {
      merge(node, 0);
    }
  } else if (idx == node->numKeys) {
    if (node->children[idx - 1]->numKeys >= ORDER / 2) {
      fill(node, idx);
    } else {
      merge(node, idx - 1);
    }
  } else {
    if (node->children[idx - 1]->numKeys >= ORDER / 2) {
      fill(node, idx);
    } else if (node->children[idx + 1]->numKeys >= ORDER / 2) {
      fill(node, idx + 1);
    } else {
      merge(node, idx);
    }
  }
}

// Function to delete a key from the B+ tree
void delete(Node **root, int key) {
  if (*root == NULL) {
    // Tree is empty
    return;
  }

  deleteNode(*root, key);

  if ((*root)->numKeys == 0) {
    Node *temp = *root;
    if ((*root)->isLeaf) {
      *root = NULL;
    } else {
      *root = (*root)->children[0];
    }
    free(temp);
  }
}

// Function to print the B+ tree
void printTree(Node *node, int depth) {
  if (node != NULL) {
    for (int i = 0; i < node->numKeys; i++) {
      LOG("%*s%d\n", depth * 4, "", node->keys[i]);
    }
    if (!node->isLeaf) {
      for (int i = 0; i <= node->numKeys; i++) {
        printTree(node->children[i], depth + 1);
      }
    }
  }
  fflush(stdout);  // для мнгновенного вывода
}

int main() {
  Node *root = NULL;

  insert(&root, 10);
  insert(&root, 20);
  insert(&root, 5);
  insert(&root, 6);
  insert(&root, 12);
  insert(&root, 30);
  insert(&root, 7);
  insert(&root, 17);

  LOG("B+ Tree:\n", NULL)
  printTree(root, 0);

  delete (&root, 12);
  delete (&root, 20);
  delete (&root, 30);
  LOG("\nB+ Tree after deletion:\n", NULL);
  printTree(root, 0);

  return 0;
}
