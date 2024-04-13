#include "iterator.h"

bool Equal(const Iterator *lhs, const Iterator *rhs)
{
    if (lhs != NULL && rhs != NULL)
    {
        return lhs->node == rhs->node;
    }
}

bool NotEqual(const Iterator *lhs, const Iterator *rhs)
{
    return !Equal(lhs, rhs);
}

Iterator *Next(Iterator *iterator)
{
    iterator->node = iterator->node->next;
    return iterator;
}

char *fetch(const Iterator *iterator)
{
    return iterator->node->data;
}

void Store(const Iterator *iterator, const char *t)
{
    if (iterator != NULL && iterator->node != NULL)
    {
        strncpy(iterator->node->data, t, sizeof(iterator->node->data) - 1);
        iterator->node->data[sizeof(iterator->node->data) - 1] = '\0';
    }
}
