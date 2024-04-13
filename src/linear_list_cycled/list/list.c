#include "list.h"

void Create(List *list)
{
    list->head = malloc(sizeof(Item));
    list->head->next = list->head;
    list->size = 0;
}

Iterator Last(const List *list)
{
    Iterator current = {list->head};
    while (current.node->next != list->head && current.node->next != NULL)
    {
        Next(&current);
    }
    return current;
}

Iterator First(const List *list)
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
    return first.node == last.node;
}

void Destroy(List *list)
{

    Iterator current = First(list);

    while (current.node != list->head)
    {
        Item *itemToFree = current.node;
        Next(&current);
        free(itemToFree);
    }
    free(list->head);
    list->head = NULL;
    list->size = 0;
}

bool Append(List *list, int pos, const char *t)
{
    if (size(list) > 0)
        pos = pos % size(list);
    Item *newItem = malloc(sizeof(Item));
    if (pos < 0)
    {
        puts("Ай-яй-яй, num должен быть > 0");
        return false;
    }

    if (!newItem)
    {
        return false;
    }

    Iterator cur = {newItem};
    Store(&cur, t);

    if (pos == 1)
    {
        // если первый элемент -- самый первый
        if (size(list) == 0) {
            newItem->next = list->head;
            list->head = newItem;
        }
        // если первый элемент -- первый после прокрутки, т.е. == последний
        else {
            pos = size(list) + 1;
            Iterator current = First(list);
            for (int i = 0; i < pos - 2; i++) {
                Next(&current);
            }
            // повторка кода ниже
            Iterator tmp = {current.node->next};

            current.node->next = newItem;
            Next(&current);
            Store(&current, t);

            current.node->next = tmp.node;
            current.node->next = list->head;
        }
    } else {

        Iterator current = First(list);
        for (int i = 0; i < pos - 2; i++) {
            Next(&current);
        }
        Iterator tmp = {current.node->next};

        current.node->next = newItem;
        Next(&current);
        Store(&current, t);

        current.node->next = tmp.node;
    }
    list->size++;
    return true;
}

bool Remove(List *list, int num)
{
    if (size(list) == 0)
    {
        return false;
    }

    Item **elem = &(list->head);
    int pos = (num % size(list)) - 1;

    for (int i = 0; i < pos; i++){
        elem = &((*elem)->next);
    }
    Item *next = (*elem)->next;
    free(*elem);
    *elem = next;
    list->size--;

    return true;
}

void PrintList(List *list)
{
    if (size(list) == 0 || list == NULL)
    {
        printf("Список-то пуст\n");
        return;
    }
    Iterator current = First(list);
    printf("[ ");
    int k = size(list);
    while (k != 0)
    {
        printf("%s ", fetch(&current));
        Next(&current);
        k--;
    }
    printf("]\n");
}

void AddLastToHead(List *list, int k)
{
    if (k <= 0)
    {
        printf("Ай-яй-яй, k должно быть > 0\n");
        return;
    }
    if (list == NULL || size(list) == 0)
    {
        printf("Пустой список!!!\n");
        return;
    }
    Iterator last = Last(list);
    while (k--)
    {
        // СОЗДАЕМ ВРЕМЕННЫЙ ОБЪЕКТ
        Item *tmp = malloc(sizeof(Item));
        if (tmp == NULL)
        {
            fprintf(stderr, "Ошибка в выделении памяти!!!");
        }
        // добавляем в него инфу из последнего элемента
        strcpy(tmp->data, fetch(&last));

        // за ним идет первый элемент
        tmp->next = list->head;

        // первый элемент теперь наш временный
        list->head = tmp;

        // количество увеличиваем
        list->size++;
    }
}