#include <stdlib.h>
#include <time.h>
#include "table.h"

void Create_Table(FILE *file, Key *keys, Data *datas)
{
    int res = 0;
    for (int i = 0; i < N; i++)
    {
        res = fscanf(file, "%s %[^\n]\n", keys[i].key_value, datas[i].data);
        keys[i].to = i;
    }
    if (res){
        puts("Таблица успешно создана");
    }
    else {
        fprintf(stderr, "Возникла ошибка при создании таблицы!\n");
    }
}

void Print_Table(const Key *keys, const Data *datas)
{
    printf("|---------------------------------------------------------|\n");
    printf("| Ключ | Строка |\n");
    printf("|---------------------------------------------------------|\n");
    for (int i = 0; i < N; i++)
    {
        printf(" %-5s | %-50s\n", keys[i].key_value, datas[keys[i].to].data);
        printf("|---------------------------------------------------------|\n");
    }
}

void CruchuVerchu(Key* keys){
    srand(time(NULL));
    for (int i = 0; i < N; i++){
        int seedA = rand() % N;
        int seedB = rand() % N;
        Key tmp = keys[seedA];
        keys[seedA] = keys[seedB];
        keys[seedB] = tmp;
    }
}

void Reverse(Key* keys)
{
    for (int i = 0; i < N / 2; i++)
    {
        Key reverse;
        reverse = keys [i];
        keys [i] = keys [N - i];
        keys [N - i] = reverse;
    }
}