#ifndef TREE_H_
#define TREE_H_

#include "symbol.h"

typedef struct Expression_node_ {
    Symbol* symbol;
    struct Expression_node_* r;
    struct Expression_node_* l;
} Expression_node;

#endif // TREE_H_
