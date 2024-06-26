//
// Created by lemito on 4/6/24.
//
#ifndef MAGICOFTHEC_LIST_CYCL_H
#define MAGICOFTHEC_LIST_CYCL_H
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../iterator/iterator.h"
#include "../../utils/utils.h"

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
Iterator First(const List *list);

/**
 * Ищем последний итератор
 * @param list
 * @return
 */
Iterator Last(const List *list);

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
 * @param pos куда вставляем
 */
bool Append(List *list, int pos, const char* t);

/**
 * @brief Удаляет элемент
 * 
 * @param list откуда удаляем
 * @param user_pos откуда удаляем?
 * @return true удален
 * @return false не удален
 * 
 */
bool Remove(List * list, int user_pos);

/**
 * @brief Добавляет последней элемент в начало K раз
 * 
 * @param list 
 * @param k сколько раз дублируется последний элемент в начале
 */
void AddLastToHead(List *list, int k);

#endif //MAGICOFTHEC_LIST_CYCL_H