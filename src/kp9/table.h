#ifndef MAGICOFTHEC_TABLE_H
#define MAGICOFTHEC_TABLE_H
#include <stdio.h>

// цифра зависит от количества строк во входной файле
#define N 14

typedef struct Key
{
    char key_value[5];
    int to;
} Key;

typedef struct Data
{
    char data[60];
} Data;

/**
 * Меняет ключи местами -- свап
 * @param a первый ключ
 * @param b второй ключ
 */
void swapify(Key* a, Key* b);

/**
 * Читает файл и создает по нему два массив: с ключами и со значениями
 * @param file входной файл
 * @param keys массив ключей
 * @param datas массив значений
 */
void Create_Table(FILE *file, Key *keys, Data *datas);

/**
 * Выводит файл в виде красивой таблички ключ | значение
 * @param keys массив ключей
 * @param datas массив значений
 */
void Print_Table(const Key *keys, const Data *datas);

/**
 * Рандомит таблицу
 * @param keys массив ключей
 */
void CruchuVerchu(Key* keys);

/**
 * Переворачивает таблицу
 * @param keys массив ключей
 */
void Reverse(Key* keys);

#endif //MAGICOFTHEC_TABLE_H
