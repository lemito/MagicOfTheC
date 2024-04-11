#include "list.h"

void Create(List *list)
{
    list->head = malloc(sizeof(Item));
    list->head->next = list->head;
    list->size = 0;
}

Item *Last(const List *list)
{
    if (size(list) == 0)
    {
        return NULL;
    }
    Item *current = list->head;
    while (current->next != list->head && current->next != NULL)
    {
        current = current->next;
    }
    return current;
}

Item * First(const List *list)
{
    return list->head;
}

int size(const List *list)
{
    return list->size;
}

bool Empty(const List *list)
{
    Item* first = First(list);
    Item *last = Last(list);
    return first == last;
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



void Append(List *list, const char *t)
{
    Item *newItem = malloc(sizeof(Item));
    if (!newItem)
    {
        return;
    }

    // тут утечка памяти
    // strcpy(newItem->data, t);

    strncpy(newItem->data, t, sizeof(newItem->data) - 1);
    newItem->data[sizeof(newItem->data) - 1] = '\0';

    newItem->next = NULL;

    Item *last = Last(list);
    if (last != NULL)
        last->next = newItem;
    else
        list->head = newItem;

    list->size++;
}

bool Remove(List *list, const char *t)
{
    if (size(list) == 0)
    {
        return false;
    }

    Item *current = list->head;
    Item *previusly = NULL;

    if (current != NULL && strcmp(current->data, t) == 0)
    {
        list->head = current->next;
        free(current);
        list->size--;
        return true;
    }

    while (current != NULL && strcmp(current->data, t) != 0)
    {
        previusly = current;
        current = current->next;
    }

    if (current == NULL)
        return false;

    previusly->next = current->next;
    free(current);
    list->size--;

    return true;
}

// Функция для ручного вывода элементов списка в нужном формате
void PrintList(List *list)
{
    if (size(list) == 0 || list == NULL)
    {
        printf("Список-то пуст\n");
        return;
    }
    Item *current = list->head;
    printf("[ ");
    while (current != NULL)
    {
        printf("%s ", current->data);
        current = current->next;
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
    Item *last = Last(list);
    while (k--)
    {
        // СОЗДАЕМ ВРЕМЕННЫЙ ОБЪЕКТ
        Item *tmp = malloc(sizeof(Item));
        if (tmp == NULL)
        {
            fprintf(stderr, "Ошибка в выделении памяти!!!");
        }
        // добавляем в него инфу из последнего элемента
        strcpy(tmp->data, last->data);

        // за ним идет первый элемент
        tmp->next = list->head;

        // первый элемент теперь наш временный
        list->head = tmp;

        // количество увеличиваем
        list->size++;
    }
}