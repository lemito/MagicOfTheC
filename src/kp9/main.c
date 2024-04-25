#include <stdio.h>

#define N 8

typedef struct Key
{
    char key_value[5];
    int to;
} Key;

typedef struct Data
{
    char data[50];
} Data;

void Create_Table(FILE *file, Key *keys, Data *datas)
{
    for (int i = 0; i < N; i++)
    {
        fscanf(file, "%s %[^\n]\n", keys[i].key_value, datas[i].data);
        keys[i].to = i;
    }
}

void Print_Table(const Key *keys, const Data *datas)
{
    printf("|---------------------------------------------------------|\n");
    printf("| Ключ | Строка |\n");
    printf("|---------------------------------------------------------|\n");
    for (int i = 0; i < N; i++)
    {
        printf(" %s | %-50s\n", keys[i].key_value, datas[keys[i].to].data);
        printf("|---------------------------------------------------------|\n");
    }
}

void heapify(int arr[], int n, int i) 
{ 
    int temp, maximum, left_index, right_index; 
  
    maximum = i; 
  
    right_index = 2 * i + 2; 
  
    left_index = 2 * i + 1; 
  
    if (left_index < n && arr[left_index] > arr[maximum]) 
        maximum = left_index; 
  
    if (right_index < n && arr[right_index] > arr[maximum]) 
        maximum = right_index; 
  
    if (maximum != i) { 
        temp = arr[i]; 
        arr[i] = arr[maximum]; 
        arr[maximum] = temp; 
        heapify(arr, n, maximum); 
    } 
} 
  
void heapsort(int arr[], int n)
{ 
    int i, temp; 

    for (i = n / 2 - 1; i >= 0; i--) { 
        heapify(arr, n, i); 
    }   
    for (i = n - 1; i > 0; i--) { 
        temp = arr[0]; 
        arr[0] = arr[i]; 
        arr[i] = temp; 
        heapify(arr, i, 0); 
    } 
} 

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void print_menu()
{
    puts("0) Выйти");
    puts("1) Печать очереди");
    puts("2) Вставика в очередь элемента в формате key:value");
    puts("3) Удалить из очереди и вывести элемент в формате key:value");
    puts("4) Длина очереди");
    puts("5) Отсортировать (метод: сортировка слиянием)");
}

int main(void)
{
    Key keys[N];
    Data data[N];
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Не удалось открыть файл\n");
        return 1;
    }
    Create_Table(input, &keys, &data);
    Print_Table(&keys, &data);
    // print_menu();
    // char choise;
    // while (scanf("%c", &choise) != EOF && choise != '0')
    // {
    //     if (choise == EOF)
    //     {
    //         break;
    //     }
    //     switch (choise)
    //     {
    //     case '1':
    //         // clearInputBuffer();
    //         break;

    //     case '2':
    //         puts("Введите ключ и значение элемента в формате key:value");
    //         // scanf("%d:%d", &worker_type.key, &worker_type.value);
    //         // if ()
    //             puts("Добавлено!");
    //         // clearInputBuffer();
    //         break;

    //     case '3':
    //         // clearInputBuffer();
    //         break;

    //     case '4':
    //         // clearInputBuffer();
    //         break;

    //     case '5':
    //         puts("Отсортировано");
    //         // clearInputBuffer();
    //         break;

    //     default:
    //         puts("Неверный вариант!");
    //         break;
    //     }
    //     print_menu();
    //     // clearInputBuffer();
    //     scanf("%c", &choise);
    // }

    // puts("Работа окончена!");

    return 0;
}