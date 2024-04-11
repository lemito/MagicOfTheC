#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief структура элемента
 * 
 */
typedef struct Item
{
    struct Item *prev;
    struct Item *next;
    char data[15];
} Item;

/**
 * @brief структура итератора
 * 
 */
typedef struct Iterator
{
    Item *node;
} Iterator;

/**
 * @brief Эквивалентность
 * 
 * @param lhs 
 * @param rhs 
 * @return true Эквивалентны
 * @return false Не экивалентны
 */
bool Equal(const Iterator *lhs, const Iterator *rhs);

/**
 * @brief Не экивалентны
 * 
 * @param lhs 
 * @param rhs 
 * @return true Не экивалентны
 * @return false Экивалентны
 */
bool NotEqual(const Iterator *lhs, const Iterator *rhs);

/**
 * @brief шаг в следующий итератор
 * 
 * @param iterator 
 * @return Iterator* 
 */
Iterator *Next(Iterator *iterator);

/**
 * @brief шаг в предыдущий итератор
 * 
 * @param iterator 
 * @return Iterator* 
 */
Iterator *Prev(Iterator *iterator);

/**
 * @brief достаем инфу из итератора
 * 
 * @param iterator 
 * @return char* строка
 */
char* fetch(const Iterator *iterator);

/**
 * @brief добавляем строку
 * 
 * @param Iterator 
 */
void Store(const Iterator *Iterator, const char*);

#endif // ITERATOR_H
