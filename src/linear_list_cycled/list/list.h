//
// Created by lemito on 4/6/24.
//
#ifndef MAGICOFTHEC_LIST_CYCL_H
#define MAGICOFTHEC_LIST_CYCL_H
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief структура элемента
 *
 */
typedef struct Item
{
//    struct Item *prev;
    struct Item *next;
    char data[25];
} Item;

typedef struct List
{
    Item *head;
    int size;
} List;

/**
 * Создаем лист
 * @param list
 */
void Create(List *list);

/**
 * Ищем первый итератор
 * @param list
 * @return
 */
Item *First(const List *list);

/**
 * Ищем последний итератор
 * @param list
 * @return
 */
Item *Last(const List *list);

/**
 * Размер
 * @param list
 * @return
 */
int size(const List *list);

/**
 * Пусто?
 * @param list
 * @return
 */
bool Empty(const List *list);

/**
 * уничножение листа
 * @param list
 */
void Destroy(List *list);

/**
 * выводим список в красивые скобочки
 * @param list
 */
void PrintList(List *list);

/**
 * То же что и Insert, только без итератора [вставка в конец]
 * @param list лист
 * @param char* кого вставляем
 */
void Append(List *list, const char* t);

/**
 * @brief Удаляет элемент
 * 
 * @param list откуда удаляем
 * @param t кого удаляем
 * @return true удален
 * @return false не удален
 */
bool Remove(List * list, const char *t);

/**
 * @brief Добавляет последней элемент в начало K раз
 * 
 * @param list 
 * @param k сколько раз дублируется последний элемент в начале
 */
void AddLastToHead(List *list, int k);

#endif //MAGICOFTHEC_LIST_CYCL_H