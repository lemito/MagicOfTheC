#include "iterator/iterator.h"
#include <stdlib.h> 

typedef struct List
{
    Item *head;
    int size;
} List;

void Create(List *list)
{
    list->head = malloc(sizeof(Item));
    list->head->next = list->head->prev = list->head;
    list->size = 0;
}

Iterator First(const List *list)
{
    Iterator res = {list->head->next};
    return res;
}

Iterator Last(const List *list)
{
    Iterator res = {list->head};
    return res;
}

int size(const List *list)
{
    return list->size;
}

bool Empty(const List *list)
{
    Iterator first = First(list);
    Iterator last = Last(list);
    return Equal(&first, &last);
}

Iterator Insert(List *list, Iterator *iterator, const int t)
{
    Iterator res = {malloc(sizeof(Item))};
    if (!res.node)
        return Last(list);
    res.node->data = t;
    res.node->next = iterator->node;
    res.node->prev = iterator->node->prev;
    res.node->prev->next = res.node;
    iterator->node->prev = res.node;
    list->size++;
    return res;
}

Iterator Delete(List *list, Iterator *iterator)
{
    Iterator res = Last(list);
    if (Equal(iterator, list))
        return res;
    res.node = iterator->node->next;
    res.node->prev = iterator->node->prev;
    iterator->node->prev->next = res.node;
    list->size--;
    free(iterator->node);
    iterator->node = NULL;
    return res;
}

Iterator Destroy(List *list){
    Item* item = list->head->next;
    while (item != list->head)
    {
        Item* previtem = item;
        item = item->next;
        free(previtem);
    }
    free(list->head);
    list->head = NULL;
    list->size = 0; 
}

int main(int argc, char const *argv[])
{
    List listik;
    Create(&listik);
    Iterator iter = First(&listik);
    Insert(&listik, &iter, 1);
    Insert(&listik, &iter, 2);
    Insert(&listik, &iter, 3);
    Destroy(&listik);
    return 0;
}
