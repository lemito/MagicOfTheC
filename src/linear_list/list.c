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

Iterator Insert(List *l, Iterator *i, const int t)
{
    Iterator res = {malloc(sizeof(
        struct Item))};
    if (!res.node)
        return Last(l);
    res.node->data = t;
    res.node->next = i->node;
    res.node->prev = i->node->prev;
    res.node->prev->next = res.node;
    i->node->prev = res.node;
    l->size++;
    return res;
}

Iterator Delete(List *list, Iterator *iterator)
{
    Iterator res = Last(list);
    if (Equal(iterator, (const Iterator *) list))
        return res;
    res.node = iterator->node->next;
    res.node->prev = iterator->node->prev;
    iterator->node->prev->next = res.node;
    list->size--;
    free(iterator->node);
    iterator->node = NULL;
    return res;
}

void Destroy(List *list)
{
    Item *item = list->head->next;
    while (item != list->head)
    {
        Item *previtem = item;
        item = item->next;
        free(previtem);
    }
    free(list->head);
    list->head = NULL;
    list->size = 0;
}

int main()
{
    List listik;
    Create(&listik); // Ensure this is the first operation on listik

    Iterator lastElem = Last(&listik);
    Insert(&listik, &lastElem, 10);
    Insert(&listik, &lastElem, 20);
    Insert(&listik, &lastElem, 30);

    Iterator it = First(&listik); // Now safe to use after Create
    for (int i = 0; i < size(&listik); i++)
    {
        int data = fetch(&it); // Assuming fetch is correctly implemented
        printf("%d\n", data);
        it = *Next(&it); // Assuming Next is correctly implemented
    }

    // Assuming NotEqual and Next are correctly implemented
    Iterator end = Last(&listik);
    for (; NotEqual(&it, &end); it = *Next(&it))
    {
        int data = fetch(&it);
        printf("%d\n", data);
    }
    Destroy(&listik);
    return 0;
}
