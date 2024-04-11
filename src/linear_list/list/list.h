//
// Created by lemito on 4/6/24.
//
#ifndef MAGICOFTHEC_LIST_H
#define MAGICOFTHEC_LIST_H
#include <stdlib.h>
#include "../iterator/iterator.h"

typedef struct List
{
    Item *head;
    int size;
} List;

void Create(List *list);

Iterator First(const List *list);

Iterator Last(const List *list);

int size(const List *list);

bool Empty(const List *list);

Iterator Insert(List *l, Iterator *i, const char* t);

Iterator Delete(List *list, Iterator *iterator);

void Destroy(List *list);
#endif //MAGICOFTHEC_LIST_H
