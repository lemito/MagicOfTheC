#include <stdio.h>
#include <stdbool.h>

typedef struct Item
{
    struct Item *prev;
    struct Item *next;
    int data;
} Item;

typedef struct Iterator
{
    Item *node;
} Iterator;

bool Equal(const Iterator *lhs, const Iterator *rhs);

bool NotEqual(const Iterator *lhs, const Iterator *rhs);

Iterator *Next(Iterator *iterator);

Iterator *Prev(Iterator *iterator);

int fetch(const Iterator *iterator);

void Store(const Iterator *Iterator, const int t);