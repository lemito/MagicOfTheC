#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <stdbool.h>

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

void print_cell(cell *current_cell)
{
    printf("Key: %s, Name: %s, Age: %s, Institute: %s, GPA: %.2f\n",
           current_cell->key,
           current_cell->value->name,
           current_cell->value->age,
           current_cell->value->institute,
           current_cell->value->gpa);
}

void print_table(Table *table)
{
    if (table == NULL)
    {
        fprintf(stdout, "Таблица пуста");
        return;
    }
    for (unsigned int i = 0; i < TABLE_SIZE; i++)
    {
        cell *current_cell = table->cells[i];
        while (current_cell != NULL)
        {
            print_cell(current_cell);
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

    while (work_cell!= NULL && strcmp(work_cell->key, key) < 0)
    {
        prev = work_cell;
        work_cell = work_cell->next;
    }

    if (work_cell!= NULL && strcmp(work_cell->key, key) == 0)
    {
        free(work_cell->value->name);
        free(work_cell->value->age);
        free(work_cell->value->institute);
        work_cell->value->name = strdup(name);
        work_cell->value->age = strdup(age);
        work_cell->value->institute = strdup(institute);
        work_cell->value->gpa = gpa;
    }
    else
    {
        cell *new_cell = create_cell(key, name, age, institute, gpa);
        if (prev == NULL)
        {
            new_cell->next = table->cells[slot];
            table->cells[slot] = new_cell;
        }
        else
        {
            new_cell->next = prev->next;
            prev->next = new_cell;
        }
    }
}


row *get_row(Table *table, const char *key)
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

cell *get_cell(Table *table, const char *key)
{
    unsigned int slot = gen_hash(key);
    cell *cell = table->cells[slot];

    while (cell != NULL)
    {
        if (strcmp(cell->key, key) == 0)
        {
            return cell;
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
            fprintf(stdout, "%.2f->%.2f\n", current_cell->value->gpa, new_gpa);
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

void clear_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

#define ADD_TO_TABLE(table, key_var, name, age, institute, gpa) \
    const char *key_var = generate_key();                       \
    set(table, key_var, name, age, institute, gpa);

bool add_to_table_from_user(Table *table)
{
    char *name = malloc(sizeof(char) * 10);
    char *age = malloc(sizeof(char) * 3);
    char *institute = malloc(sizeof(char) * 3);
    float gpa = 0.0f;

#define CLEAR_VARS_IN_ADD_FROM_USER \
    FREE_AND_NULL(name);            \
    FREE_AND_NULL(age);             \
    FREE_AND_NULL(institute);

    if (!name || !age || !institute)
    {
        fprintf(stderr, "Ошибка выделения памяти\n");
        CLEAR_VARS_IN_ADD_FROM_USER;
        return false;
    }

    puts("Добавление нового студента:");
    printf("Имя:\n▷▷▷ ");
    if (scanf("%9s", name) != 1)
    {
        fprintf(stderr, "Ошибка при вводе имени\n");
        CLEAR_VARS_IN_ADD_FROM_USER;
        return false;
    }
    clear_stdin();
    printf("\nВозраст:\n▷▷▷ ");
    if (scanf("%2s", age) != 1)
    {
        fprintf(stderr, "Ошибка при вводе возраста\n");
        CLEAR_VARS_IN_ADD_FROM_USER;
        return false;
    }
    clear_stdin();
    printf("\nИнститут:\n▷▷▷ ");
    if (scanf("%2s", institute) != 1)
    {
        fprintf(stderr, "Ошибка при вводе института\n");
        CLEAR_VARS_IN_ADD_FROM_USER;
        return false;
    }
    clear_stdin();
    printf("\nОценка:\n▷▷▷ ");
    if (scanf("%f", &gpa) != 1)
    {
        fprintf(stderr, "Ошибка при вводе оценки\n");
        CLEAR_VARS_IN_ADD_FROM_USER;
        return false;
    }
    if (gpa > 5.00f) {
        printf("Оценка не может быть больше 5.00\n");
        CLEAR_VARS_IN_ADD_FROM_USER;
        return false;
    }
    clear_stdin();
    ADD_TO_TABLE(table, key, name, age, institute, gpa);
    CLEAR_VARS_IN_ADD_FROM_USER;
    return true;
}

char *search_name_by_key(Table *table, char *key)
{
    if (table == NULL)
        fprintf(stderr, "Нет таблицы");
    for (unsigned int i = 0; i < TABLE_SIZE; i++)
    {
        cell *current_cell = table->cells[i];
        while (current_cell != NULL)
        {
            if (strcmp(current_cell->key, key) == 0)
            {
                return current_cell->value->name;
            }
            current_cell = current_cell->next;
        }
    }
    printf("Студент с ключом: %s не найден в таблице\n", key);
    return NULL;
}

char *search_key_by_name(Table *table, char *name)
{
    if (table == NULL)
        fprintf(stderr, "Нет таблицы");
    for (unsigned int i = 0; i < TABLE_SIZE; i++)
    {
        cell *current_cell = table->cells[i];
        while (current_cell != NULL)
        {
            if (strcmp(current_cell->value->name, name) == 0)
            {
                return current_cell->key;
            }
            current_cell = current_cell->next;
        }
    }
    printf("Студент с именем: %s не найден в таблице\n", name);
    return NULL;
}

void write_table_to_file(Table *pTable, FILE *pFile) {
        if (pTable == NULL)
        {
            fprintf(stdout, "Таблица пуста");
            return;
        }
        for (unsigned int i = 0; i < TABLE_SIZE; i++)
        {
            cell *current_cell = pTable->cells[i];
            while (current_cell != NULL)
            {
                fprintf(pFile, "Key: %s, Name: %s, Age: %s, Institute: %s, GPA: %.2f\n",
                       current_cell->key,
                       current_cell->value->name,
                       current_cell->value->age,
                       current_cell->value->institute,
                       current_cell->value->gpa);
                current_cell = current_cell->next;
            }
        }
}

void print_menu()
{
    puts("Меню:");
    puts("1. Добавить студента");
    puts("2. Удалить студента по имени");
    puts("3. Изменить GPA студенту");
    puts("4. Показать средний GPA по институту");
    puts("5. Вывести всю таблицу");
    puts("0. Выход");
    puts("Выберите действие: ");
}

int main(void)
{
    Table *my = create_table();
    int choice;
    char input[256];
    bool is_running = true;

    while (is_running)
    {
        print_menu();
        if (scanf("%d", &choice) != 1)
        {
            printf("Ошибка ввода. Попробуйте снова.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            if (!add_to_table_from_user(my))
            {
                fprintf(stderr, "Ошибка при добавлении студента!\n");
            }
            break;
        case 2:
            printf("Введите имя студента для удаления: ");
            scanf("%255s", input);
            delete_by_name(my, input);
            break;
        case 3:
            printf("Введите имя студента, которому нужно изменить GPA: ");
            scanf("%255s", input);
            printf("Введите новое значение GPA: ");
            float new_gpa_in;
            if (scanf("%f", &new_gpa_in) != 1)
            {
                printf("Ошибка ввода GPA. Попробуйте снова.\n");
                break;
            }
            if (new_gpa_in > 5.00f) {
                printf("Оценка не может быть больше 5.00\n");
                break;
            }
            new_gpa(my, search_key_by_name(my, input), new_gpa_in);
            break;
        case 4:
            printf("Введите номер института для расчета среднего GPA: ");
            scanf("%255s", input);
            print_average_gpa_by_institute(my, input);
            break;
        case 5:
            print_table(my);
            break;
        case 6:
            printf("Введите название файла для сохранения: ");
            char file_name[25];
            scanf("%24s", file_name);
            FILE* output = fopen(file_name, "w");
            write_table_to_file(my, output);
        case 0:
            is_running = false;
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    free_table(my);
    return EXIT_SUCCESS;
}

