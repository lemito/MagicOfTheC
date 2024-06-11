#include <stddef.h>
#include "../vector/vector_lib.h"

typedef struct Item
{
    int data;          // хранимое значение
    struct Item *next; // указатель на следующий элемент
    struct Item *prev; // указатель на предыдущий элемент
} Item;
typedef struct deque
{
    Item *left;  // указатель на левый конец дека
    Item *right; // указатель на правый конец дека
    int size;    // размер дека
} deque;

deque *CreateDeque(Vector *v);        // создание дека из вектора
bool isEmptyDeque(deque *d);          // проверка отсутствия элементов в деке
bool PushLeftDeque(deque *d, int i);  // добавить элемент с левого конца
bool PushRightDeque(deque *d, int i); // добавить элемент с правого конца
bool PopLeftDeque(deque *d);          // взять элемент с левого конца
bool PopRightDeque(deque *d);         // взять элемент с правого конца
int TopLeftDeque(deque *d);           // посмотреть элемент с левого конца
int TopRightDeque(deque *d);          // посмотреть элемент с правого конца
bool DeleteDeque(deque *d);           // очистить дек

// создание дека из вектора
deque *CreateDeque(Vector *v)
{
    deque *d = (deque *)malloc(sizeof(deque));
    d->size = 0;
    d->left = 0;
    d->right = 0;
    for (int i = 0; i < v->size; ++i)
        PushLeftDeque(d, Load(v, i));
    return d;
}
// проверка отсутствия элементов в деке
bool isEmptyDeque(deque *d)
{
    if (d->size == 0)
        return true;
    return false;
}
// добавить элемент с левого конца
bool PushLeftDeque(deque *d, int i)
{
    Item *q = 0;
    if (d->left)
    {
        q = d->left;
        d->left = d->left->prev;
    }
    d->left = (Item *)malloc(sizeof(Item));
    d->left->data = i;
    d->left->next = q;
    if (d->left->next)
        d->left->next->prev = d->left;
    d->left->prev = 0;
    if (!q)
        d->right = d->left;
    d->size++;
    return true;
}
// добавить элемент с правого конца
bool PushRightDeque(deque *d, int i)
{
    Item *q = 0;
    if (d->right != 0)
    {
        q = d->right;
        d->right = d->right->next;
    }
    d->right = (Item *)malloc(sizeof(Item));
    d->right->data = i;
    d->right->next = 0;
    d->right->prev = q;
    if (d->right->prev)
        d->right->prev->next = d->right;
    if (!q)
        d->left = d->right;
    d->size++;
    return false;
}
// взять элемент с левого конца
bool PopLeftDeque(deque *d)
{
    if (isEmptyDeque(d))
        return false;
    Item *q;
    q = d->left->next;
    free(d->left);
    d->size--;
    d->left = q;
    if (d->size == 0)
    {
        d->right = d->left;
        return true;
    }
    d->left->prev = 0;
    return true;
}
// взять элемент с правого конца
bool PopRightDeque(deque *d)
{
    if (isEmptyDeque(d))
        return false;
    Item *q;
    q = d->right->prev;
    free(d->right);
    d->size--;
    d->right = q;
    if (d->size == 0)
    {
        d->left = d->right;
        return true;
    }
    d->right->next = 0;
    return true;
}
// посмотреть элемент с левого конца
int TopLeftDeque(deque *d)
{
    if (isEmptyDeque(d))
        return -1;
    // ошибка, обращение к нулевому указателю
    return d->left->data;
}
// посмотреть элемент с правого конца
int TopRightDeque(deque *d)
{
    if (isEmptyDeque(d))
        return -1;
    // ошибка, обращение к нулевому указателю
    return d->right->data;
}
// удалить дек
bool RemoveDeque(deque *d)
{
    if (isEmptyDeque(d))
        return false;
    Item *q;
    q = d->left->next;
    free(d->left);
    d->size--;
    if (q == 0)
    {
        d->left = d->right = q;
        return true;
    }
    d->left = q;
    d->left->prev = 0;
    return RemoveDeque(d);
}

int main(void)
{
    Vector v;
    Create(&v, 4);
    //    Save(&v, 0, 5);
    //    Save(&v, 1, 3);
    //    Save(&v, 2, 7);
    deque *dq = CreateDeque(&v);
    PushLeftDeque(dq, 10); // Добавляем 10 в начало очереди [10, 5, 3, 7]
    PushLeftDeque(dq, 11);
    PushRightDeque(dq, 20); // Добавляем 20 в конец очереди [10, 5, 3, 7, 20]
    PushRightDeque(dq, 21);
    if (PopLeftDeque(dq))
        puts("Попнуто слева"); // [ 5, 3, 7, 20]
    if (PopRightDeque(dq))
        puts("Попнуто справа"); // [5, 3, 7]
    printf("%d\n", TopLeftDeque(dq));
    printf("%d\n", TopRightDeque(dq));
    RemoveDeque(dq);
}