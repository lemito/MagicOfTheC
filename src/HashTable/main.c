#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>
#include <sys/types.h>

#define FREE_AND_NULL(p) \
    do                   \
    {                    \
        free(p);         \
        p = NULL;        \
    } while (0)

#define TABLE_SIZE 100
#define SEED 5

typedef struct row
{
    char *name;
    char *age;
    char *institute;
    float gpa;
} row;

typedef struct cell
{
    char *key;
    row *value;
    struct cell *next;
} cell;

typedef struct Table
{
    cell **cells;
} Table;

unsigned int gen_hash(const char *key)
{
    unsigned int hash = 0;
    while (*key)
    {
        hash = (hash << SEED) + *key++;
    }
    return hash % TABLE_SIZE;
}

cell *create_cell(const char *key, const char *name, const char *age, const char *institute, const float gpa)
{
    cell *res = malloc(sizeof(cell));
    res->key = strdup(key);
    res->value = malloc(sizeof(row));
    res->value->name = strdup(name);
    res->value->age = strdup(age);
    res->value->institute = strdup(institute);
    res->value->gpa = gpa;

    res->next = NULL;
    return res;
}

void print_table(Table *table)
{
    for (unsigned int i = 0; i < TABLE_SIZE; i++)
    {
        cell *current_cell = table->cells[i];
        while (current_cell != NULL)
        {
            printf("Key: %s, Name: %s, Age: %s, Institute: %s, GPA: %.2f\n",
                   current_cell->key,
                   current_cell->value->name,
                   current_cell->value->age,
                   current_cell->value->institute,
                   current_cell->value->gpa);
            current_cell = current_cell->next;
        }
    }
}

void free_cell(cell *cell)
{
    FREE_AND_NULL(cell->key);
    FREE_AND_NULL(cell->value->name);
    FREE_AND_NULL(cell->value->age);
    FREE_AND_NULL(cell->value->institute);
    FREE_AND_NULL(cell->value);
    FREE_AND_NULL(cell);
}

Table *create_table()
{
    Table *res = malloc(sizeof(Table));
    res->cells = calloc(TABLE_SIZE, sizeof(cell *));

    return res;
}

void set(Table *table, const char *key, const char *name, const char *age, const char *institute, const float gpa)
{
    unsigned int slot = gen_hash(key);
    cell *work_cell = table->cells[slot];
    cell *prev = NULL;

    if (work_cell == NULL)
    {
        table->cells[slot] = create_cell(key, name, age, institute, gpa);
        return;
    }

    while (work_cell != NULL)
    {
        if (strcmp(work_cell->key, key) == 0)
        {
            free(work_cell->value->name);
            free(work_cell->value->age);
            free(work_cell->value->institute);
            work_cell->value->name = strdup(name);
            work_cell->value->age = strdup(age);
            work_cell->value->institute = strdup(institute);
            work_cell->value->gpa = gpa;
            return;
        }
        prev = work_cell;
        work_cell = work_cell->next;
    }

    prev->next = create_cell(key, name, age, institute, gpa);
}

row *get(Table *table, const char *key)
{
    unsigned int slot = gen_hash(key);
    cell *cell = table->cells[slot];

    while (cell != NULL)
    {
        if (strcmp(cell->key, key) == 0)
        {
            return cell->value;
        }
        cell = cell->next;
    }

    return NULL;
}

void delete(Table *table, const char *key)
{
    unsigned int slot = gen_hash(key);
    cell *work_cell = table->cells[slot];
    cell *prev = NULL;

    while (work_cell != NULL)
    {
        if (strcmp(work_cell->key, key) == 0)
        {
            if (prev == NULL)
            {
                table->cells[slot] = work_cell->next;
            }
            else
            {
                prev->next = work_cell->next;
            }
            free_cell(work_cell);
            return;
        }
        prev = work_cell;
        work_cell = work_cell->next;
    }
}

void delete_by_name(Table *table, const char *name)
{
    for (unsigned int i = 0; i < TABLE_SIZE; i++)
    {
        cell *work_cell = table->cells[i];
        cell *prev = NULL;
        while (work_cell != NULL)
        {
            if (strcmp(work_cell->value->name, name) == 0)
            {
                if (prev == NULL)
                {
                    table->cells[i] = work_cell->next;
                }
                else
                {
                    prev->next = work_cell->next;
                }
                free_cell(work_cell);
                return;
            }
            prev = work_cell;
            work_cell = work_cell->next;
        }
    }
    printf("Студент с именем '%s' не найден.\n", name);
}

void clear_table(Table *table)
{
    for (uint i = 0; i < TABLE_SIZE; ++i)
    {
        cell *cur_cell = table->cells[i];
        cell *next_cell = NULL;
        while (cur_cell != NULL)
        {
            next_cell = cur_cell->next;
            if (cur_cell != NULL)
            {
                printf("Name cur=%s | ", cur_cell->value->name);
            }
            free_cell(cur_cell);
            cur_cell = next_cell;
        }
        table->cells[i] = NULL;
    }
}

void free_table(Table *table)
{
    clear_table(table);
    FREE_AND_NULL(table->cells);
    FREE_AND_NULL(table);
}

const char *generate_key()
{
    static char key[64];
    static unsigned long counter = 0;
    time_t now = time(NULL);
    unsigned long random_part;

    srand((unsigned int)now + counter);
    random_part = (unsigned long)rand();

    counter++;

    snprintf(key, sizeof(key), "%ld%lu%lu", (long)now, random_part, counter);

    return key;
}

void new_gpa(Table *table, const char *key, float new_gpa)
{
    unsigned int slot = gen_hash(key);
    cell *current_cell = table->cells[slot];

    while (current_cell != NULL)
    {
        if (strcmp(current_cell->key, key) == 0)
        {
            current_cell->value->gpa = new_gpa;
            return;
        }
        current_cell = current_cell->next;
    }

    printf("Ячейка с ключом '%s' не найдена.\n", key);
}

float average_gpa_by_institute(Table *table, const char *institute)
{
    float total_gpa = 0.0f;
    int cnt = 0;
    if (table == NULL)
        fprintf(stderr, "Нет таблицы");
    for (unsigned int i = 0; i < TABLE_SIZE; i++)
    {
        cell *current_cell = table->cells[i];
        while (current_cell != NULL)
        {
            if (strcmp(current_cell->value->institute, institute) == 0)
            {
                total_gpa += current_cell->value->gpa;
                cnt++;
            }
            current_cell = current_cell->next;
        }
    }

    if (cnt > 0)
    {
        return total_gpa / cnt;
    }
    else
    {
        printf("Студенты из института '%s' не найдены.\n", institute);
        return -1.0f;
    }
}

void print_average_gpa_by_institute(Table *my, const char *institute_name)
{
    float average_gpa = average_gpa_by_institute(my, institute_name);
    if (average_gpa > 0)
    {
        printf("Среднее значение GPA для института '%s': %.2f\n", institute_name, average_gpa);
    }
}

#define ADD_TO_TABLE(table, key_var, name, age, institute, gpa) \
    const char *key_var = generate_key();                       \
    set(table, key_var, name, age, institute, gpa);

int main(void)
{
    printf("hash1 = %d\n", gen_hash("Клубника"));
    printf("hash2 = %d\n", gen_hash("Клубника"));

    Table *my = create_table();

    ADD_TO_TABLE(my, key1, "Иван", "18", "8", 4.5f);
    ADD_TO_TABLE(my, key2, "Вова", "19", "8", 4.44f);
    ADD_TO_TABLE(my, key3, "Петя", "19", "4", 3.84f);
    ADD_TO_TABLE(my, key4, "Денис", "19", "4", 3.44f);
    puts("==============");
    print_table(my);
    puts("==============");

    printf("Поиск по ключу = %s : \n", key1);
    row *info = get(my, key1);
    if (info)
    {
        printf("Name: %s, Age: %s, Institute: %s, GPA: %.2f\n", info->name, info->age, info->institute, info->gpa);
    }
    puts("==============");
    puts("Удаление");
    delete_by_name(my, "Иван");
    puts("==============");
    print_table(my);
    puts("==============");
    new_gpa(my, key4, 4.01f);
    print_table(my);
    puts("==============");
    print_average_gpa_by_institute(my, "8");
    print_average_gpa_by_institute(my, "3");
    puts("==============");
    puts("Удаление таблицы:");
    free_table(my);

    return EXIT_SUCCESS;
}
