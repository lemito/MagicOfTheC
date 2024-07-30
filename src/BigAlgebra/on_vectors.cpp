#include <iostream>
#include <cstdlib>
#include <cstring>

#define MAX_INPUT_LENGTH 1024
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define FREE_AND_NULL(p) \
    do                   \
    {                    \
        free(p);         \
        (p) = nullptr;      \
    } while (0)

typedef struct Vector
{
    int *data;
    size_t size;
} Vector;

void vector_init(Vector *v, size_t sz)
{
    v->size = sz;
    v->data = (int*)malloc(v->size * sizeof(int));
    memset(v->data, 0, v->size * sizeof(int));
}

#define VECTOR_INIT(name, sz) Vector name; vector_init(&name, sz)

bool vector_isEmpty(Vector *v)
{
    return v->size == 0;
}

size_t vector_size(Vector *v)
{
    return v->size;
}

void vector_save(Vector *v, size_t i, int t)
{
    if (i < v->size)
    {
        v->data[i] = t;
    }
}

void vector_resize(Vector *v, size_t sz)
{
    void *new_data = realloc(v->data, sz * sizeof(int));
    if (new_data) {
        v->data = (int*)new_data;
        v->size = sz;
    } else {
        printf("Error in resizing!!!");
    }
}

int vector_load(Vector *v, size_t i)
{
    if (i < v->size)
    {
//        Resize(v, v->size++);
        return v->data[i];
    }
    else
    {
        return -1;
    }
}

bool vector_isEqual(Vector *l, Vector *r)
{
    if (l->size != r->size)
    {
        return false;
    }
    for (int i = 0; i < l->size; i++)
    {
        if (l->data[i] != r->data[i])
        {
            return false;
        }
    }
    return true;
}

void vector_destroy(Vector *v) {
    if (v!= nullptr) {
        if (v->data!= nullptr) {
            FREE_AND_NULL(v->data);
        }
    }
}


void one_right(int** nums_ptr, size_t* size_ptr) {
    size_t new_size = (*size_ptr) + 1;
    *nums_ptr = (int *)realloc(*nums_ptr, new_size * sizeof(int));
    for (size_t i = new_size - 1; i > 0; --i) {
        (*nums_ptr)[i] = (*nums_ptr)[i - 1];
    }
    (*nums_ptr)[0] = 0;
    *size_ptr = new_size;
}

int * num_builder(size_t size){
    int *res = (int *)malloc(size * sizeof(int));
    if (res == nullptr){
        perror("Вупси-дупси");
        exit(EXIT_FAILURE);
    }
    memset(res  , 0, sizeof(int) * size);
    return res;
}

// 0123456789+0123456789=246913578
Vector sum(Vector& num1, Vector& num2) {
    if (vector_isEmpty(&num1) || vector_isEmpty(&num2)){
        perror("Ты складываешь два пустых числа!");
    }
    size_t max_size = MAX(vector_size(&num1), vector_size(&num2));
    VECTOR_INIT(res, max_size + 1);
    int add = 0;

    for (size_t i = 0; i <= max_size; ++i) {
        // ========= для чисел разной длинны (ставится либо число, либо 0) =============
        int digit1 = (i < vector_size(&num1))? vector_load(&num1, vector_size(&num1) - 1 - i) : 0;
        int digit2 = (i < vector_size(&num2))? vector_load(&num2, vector_size(&num2) - 1 - i) : 0;
        // =============================================================================

        int sum = digit1 + digit2 + add;
        vector_save(&res, max_size - i, sum % 10);
        add = sum / 10;add = sum / 10;
    }
    vector_save(&res, 0, add);

    if (vector_load(&res, 0) == 0) {
        for (size_t i = 0; i < max_size; ++i) {
            vector_save(&res, i, vector_load(&res, i + 1));
        }
        vector_resize(&res, max_size);
    }

    return res;
}
Vector minus(Vector& num1, Vector& num2) {
    if (vector_isEmpty(&num1) || vector_isEmpty(&num2)) {
        perror("Ты вычитаешь два пустых числа!");
    }
    size_t max_size = MAX(vector_size(&num1), vector_size(&num2));
    VECTOR_INIT(res, max_size);
    int add = 0;
    vector_save(&res, 1, 0);
    for (size_t i = 0; i <= max_size; ++i) {
        int digit1 = (i < vector_size(&num1))? vector_load(&num1, vector_size(&num1) - 1 - i) : 0;
        int digit2 = (i < vector_size(&num2))? vector_load(&num2, vector_size(&num2) - 1 - i) : 0;
        int pre_res = digit1 - digit2 - add;
        if (pre_res < 0) {
            vector_save(&num1, vector_size(&num1) - i, vector_load(&num1, vector_size(&num1) - i) - 1);
            pre_res += 10;
            add++;
            printf(" _%d_ ", vector_load(&num1, vector_size(&num1) - i + 1));

        }
        printf("%d-%d==%d i=%zu\n", digit1, digit2, pre_res, i);
        vector_save(&res, max_size - i - 1, pre_res);
    }

    if (vector_load(&res, 0) == 0) {
        for (size_t i = 0; i < max_size; ++i) {
            vector_save(&res, i, vector_load(&res, i + 1));
        }
        vector_resize(&res, max_size);
    }

    return res;
}
//Vector minus(Vector& num1, Vector& num2) {
//    if (vector_isEmpty(&num1) || vector_isEmpty(&num2)){
//        perror("Ты вычитаешь два пустых числа!");
//    }
//    size_t max_size = MAX(vector_size(&num1), vector_size(&num2));
//    VECTOR_INIT(res, max_size);
//
//    int add = 0;
//    vector_save(&res, 0, add);
//    for (size_t i = 0; i <= max_size; ++i) {
//        // ========= для чисел разной длинны (ставится либо число, либо 0) =============
//        int digit1 = (i < vector_size(&num1))? vector_load(&num1, vector_size(&num1) - 1 - i) : 0;
//        int digit2 = (i < vector_size(&num2))? vector_load(&num2, vector_size(&num2) - 1 - i) : 0;
//        // =============================================================================
//        int pre_res = digit1 - digit2;
//        if (pre_res < 0){
//            pre_res = (digit1 - digit2) + 10;
//            vector_save(&num1, vector_size(&num1) - i, vector_load(&num1, vector_size(&num1) - i) - 1);
//
//        }
//        printf(" %d-%d==%d i=%zu ", digit1, digit2, pre_res, i);
//        vector_save(&res, max_size - i - 1, pre_res);
//
//    }
//
//
//    if (vector_load(&res, 0) == 0) {
//        for (size_t i = 0; i < max_size; ++i) {
//            vector_save(&res, i, vector_load(&res, i + 1));
//        }
//        vector_resize(&res, max_size);
//    }
//
//    return res;
//
//}

Vector mult(Vector& num1, Vector& num2) {
    if (vector_isEmpty(&num1) || vector_isEmpty(&num2)) {
        perror("Ты умножаешь два пустых числа!");
        return (Vector){nullptr, 0};
    }
    size_t size1 = vector_size(&num1);
    size_t size2 = vector_size(&num2);

    VECTOR_INIT(res, size1 + size2);

    // двойной цикл: i - для числа "сверху", j - "снизу"
    for (size_t i = 0; i < size1; ++i) {
        int add = 0;
        for (size_t j = 0; j < size2; ++j) {
            // результат записываем с конца
            int pre_res = vector_load(&num1, size1 - 1 - i) * vector_load(&num2, size2 - 1 - j) + vector_load(&res, res.size - 1 - (i + j)) + add;
            vector_save(&res, res.size - 1 - (i + j), pre_res % 10);
            add = pre_res / 10;
        }
        vector_save(&res, res.size - 1 - (i + size2), add);
    }

    size_t start_index = 0;
    while (start_index < res.size - 1 && vector_load(&res, start_index) == 0) {
        ++start_index;
    }

    if (start_index > 0) {
        for (size_t i = start_index; i < res.size; ++i) {
            vector_save(&res, i - start_index, vector_load(&res, i));
        }
        vector_resize(&res, res.size - start_index);
    }

    return res;
}


void print_vector(Vector& vec){
    for (int i = 0; i < vector_size(&vec); ++i) {
        std::cout << vector_load(&vec, i);
    }
}



void load_big_number(Vector *v, unsigned long long num)
{
    char str_num[21];
    sprintf(str_num, "%llu", num);
    size_t len = strlen(str_num);
    vector_init(v, len);
    for (int i = 0; i < len; ++i) {
        vector_save(v, i, str_num[i] - '0');
    }
}

void load_big_number_from_str(Vector *v, const char* num_str)
{
    size_t len = strlen(num_str);
    vector_init(v, len);
    for (size_t i = 0; i < len; ++i) {
        vector_save(v, i, num_str[i] - '0');
    }
}

void read_and_load(Vector *v, char* num_str){
    if (fgets(num_str, MAX_INPUT_LENGTH, stdin) != NULL) {
        num_str[strcspn(num_str, "\n")] = 0;
        load_big_number_from_str(v, num_str);
    }
    else{
        perror("Не удалось считать строку");
    }
}

int main(){
    VECTOR_INIT(num1, 1);
    VECTOR_INIT(num2, 1);
    VECTOR_INIT(num3, 1);

    char inputStr[MAX_INPUT_LENGTH];

    printf("Введите первое число: ");
    read_and_load(&num1, inputStr);

    printf("Введите второе число: ");
    read_and_load(&num2, inputStr);

    print_vector(num1);
    std::cout << "+";
    print_vector(num2);
    std::cout << "=";

    num3 = sum(num1, num2);
    print_vector(num3);

    std::cout << "\n";

    print_vector(num1);
    std::cout << "*";
    print_vector(num2);
    std::cout << "=";

    num3 = mult(num1, num2);
    print_vector(num3);

    std::cout << "\n";

    print_vector(num1);
    std::cout << "-";
    print_vector(num2);
    std::cout << "=";

    num3 = minus(num1, num2);
    print_vector(num3);

    vector_destroy(&num1);
    vector_destroy(&num2);
    vector_destroy(&num3);

    return EXIT_SUCCESS;
}


// C realisation
//int* sum(const int* num1, const int* num2, size_t size1, size_t size2) {
//    if (num1 == nullptr || num2 == nullptr) {
//        perror("Числа не должны быть пустыми!");
//        exit(EXIT_FAILURE);
//    }
//
//    size_t max_size = MAX(size1, size2);
//    int* res = num_builder(max_size + 1);
//    int add = 0;
//
//    for (size_t i = 0; i < max_size; ++i) {
//        // для чисел разной длинны (ставится либо число, либо 0)
//        int digit1 = (i < size1) ? num1[size1 - 1 - i] : 0;
//        int digit2 = (i < size2) ? num2[size2 - 1 - i] : 0;
//        // =====================================================
//
//        int sum = digit1 + digit2 + add;
//
//        res[max_size - i] = sum % 10;
//        add = sum / 10;
//    }
//    res[0] = add;
//
//    if (res[0] == 0) {
//        for (size_t i = 0; i <= max_size; ++i) {
//            res[i] = res[i + 1];
//        }
//    }
//
//    return res;
//}
//
//void print_num(int* num, size_t size){
//    for (int i = 0; i < size; ++i) {
//        printf("%d", num[i]);
//    }
//}
//
//int main(){
//    size_t size1 = 10;
//    int* num1 = num_builder(size1);
//    for (int i = 0; i < size1; i++) {
//        num1[i] = i;
//    }
//    size_t size2 = 10;
//    int* num2 = num_builder(size2);
//    for (int i = 0; i < size2; i++) {
//        num2[i] = i;
//    }
//
//    print_num(num1, 10);
//    printf("\n");
//    print_num(num2, 10);
//    printf("\n");
//    int* num3 = sum(num1, num2, size1, size2);
//    printf("\n");
//    print_num(num3, 10);
//    printf("\n");
//
//    FREE_AND_NULL(num1);
//    FREE_AND_NULL(num2);
//    FREE_AND_NULL(num3);
//
//    return EXIT_SUCCESS;
//}