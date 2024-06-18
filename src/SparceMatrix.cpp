#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>

typedef struct Item
{
    uint32_t row;
    uint32_t column;
    int32_t data;
} Item;

void shiftRight(Item *from, uint32_t count, uint32_t shiftSize);
void shiftLeft(Item *from, uint32_t count, uint32_t shiftSize);
void createItemAt(Item *item, int32_t data, uint32_t i, uint32_t j);

typedef struct SparceMatrix
{
    Item *items;
    uint32_t rows;
    uint32_t columns;
    uint32_t size;
    uint32_t capacity;
} SparceMatrix;

Item *find(SparceMatrix *matrix, uint32_t i, uint32_t j)
{
    if (i > matrix->rows || matrix->size == 0)
    {
        return &matrix->items[matrix->size];
    }

    Item *curr = matrix->items;
    Item *last = &matrix->items[matrix->size];
    while (curr != last && curr->row < i)
        curr++;
    while (curr != last && curr->row == i & curr->column < j)
        curr++;
    return curr;
}

int32_t GetAt(SparceMatrix *matrix, uint32_t i, uint32_t j)
{
    Item *curr = find(matrix, i, j);
    if (curr->row == i && curr->column == j)
    {
        return curr->data;
    }
    return 0;
}

void SetAt(SparceMatrix *matrix, uint32_t i, uint32_t j, int32_t data)
{
    Item *currentItem = find(matrix, i, j);
    uint32_t currentIndex = currentItem - matrix->items;
    if (currentItem->row == i && currentItem->column == j)
    {
        if (data == 0)
        {
            uint32_t tailSize = matrix->size - (currentItem - matrix->items);
            shiftLeft(currentItem, tailSize, 1);
            --matrix->size;
        }
        else
        {
            createItemAt(currentItem, data, i, j);
        }
        return;
    }
    if (data == 0)
    {
        return;
    }
    ++matrix->size;
    if (matrix->size >= matrix->capacity)
    {
        matrix->capacity += matrix->size / 2 + 1;
        matrix->items = (Item *)realloc(matrix->items, sizeof(Item) *
                                                           matrix->capacity);

        currentItem = &matrix->items[currentIndex];
    }
    uint32_t tailSize = (matrix->size - 1) - (currentItem - matrix->items);
    shiftRight(currentItem, tailSize, 1);
    createItemAt(currentItem, data, i, j);
}
void shiftLeft(Item *from, uint32_t count, uint32_t shiftSize)
{
    for (int32_t i = 0; i < count; ++i)
    {
        from[i] = from[i + shiftSize];
    }
}
void createItemAt(Item *item, int32_t data, uint32_t i, uint32_t j)
{
    item->data = data;
    item->row = i;
    item->column = j;
}
void shiftRight(Item *from, uint32_t count, uint32_t shiftSize)
{
    for (int32_t i = count; i >= 0; --i)
    {
        from[i + shiftSize] = from[i];
    }
}

void  initMatrix(SparceMatrix* matric, uint32_t rows, uint32_t columns, uint32_t size, uint32_t capacity){
    matric->items = (Item *)malloc(capacity * sizeof(Item));
    matric->size = size;
    matric->capacity = capacity;
    matric->rows = rows;
    matric->columns = columns;
}

int32_t scalyar(SparceMatrix* first, SparceMatrix* second){
    int32_t res = 0;
    uint32_t cnt = first->columns;
    for (uint32_t j = 0; j < cnt; ++j){
        int32_t val1 = GetAt(first, j, 1);
        int32_t val2 = GetAt(second, j, 1);
        std::cout << "+" << val1*val2 << "_";
        res += val1 * val2;
    }
    return res;
}

int main()
{
    SparceMatrix vector1;
    SparceMatrix vector2;
    initMatrix(&vector1, 1, 5, 2, 2);
    initMatrix(&vector2, 1, 5, 3, 3);
    // vector1
    SetAt(&vector1, 0, 1, 5);
    SetAt(&vector1, 0, 3, 10);
    // vector2
    SetAt(&vector2, 0, 1, 5);
    SetAt(&vector2, 0, 3, 10);
    SetAt(&vector2, 0, 4, 15);

    std::cout << "vector1" << std::endl;
    for (uint32_t j = 0; j < vector1.columns; ++j)
    {
        int32_t value = GetAt(&vector1, 0, j);
        std::cout << "vec[" << j << "] = " << value << std::endl;
    }
    std::cout << "vector2" << std::endl;
    for (uint32_t j = 0; j < vector2.columns; ++j)
    {
        int32_t value = GetAt(&vector2, 0, j);
        std::cout << "vec[" << j << "] = " << value << std::endl;
    }
    std::cout << "scalyar vector1*vector2";
    std::cout << "=" << scalyar(&vector1, &vector2);

    free(vector1.items);
    free(vector2.items);
    return 0;
}