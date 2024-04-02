#include <stdio.h>
#include <stdbool.h>
#include "iterator.h"


bool Equal(const Iterator* lhs, const Iterator* rhs){
    return lhs->node == rhs->node;
}

bool NotEqual(const Iterator* lhs, const Iterator* rhs){
    return !Equal(lhs, rhs);
}

Iterator* Next(Iterator* iterator){
    iterator->node = iterator->node->next;
    return iterator;
}

Iterator* Prev(Iterator* iterator){
    iterator->node = iterator->node->prev;
    return iterator;
}

int fetch(const Iterator* iterator){
    return iterator->node->data;
}

void Store(const Iterator* Iterator, const int t){
    Iterator->node->data = t;
}

// int main(int argc, char const *argv[])
// {
//     /* code */
//     return 0;
// }

