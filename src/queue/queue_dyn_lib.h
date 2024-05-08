#include <stdbool.h>
#include "../utils/utils.h"

/**
 * @brief 
 * 
 */
struct Item
{
    char data[25];
    struct Item *next;
};

/**
 * @brief 
 * 
 */
typedef struct queue
{
    struct Item *first;
    struct Item *last;
    int size;
} queue;

/**
 * @brief 
 * 
 * @param q 
 */
void Create(queue *q);

/**
 * @brief 
 * 
 * @param q 
 * @return true 
 * @return false 
 */
bool Empty(queue *q);

/**
 * @brief 
 * 
 * @param q 
 * @return int 
 */
int Size(queue *q);

/**
 * @brief 
 * 
 * @param q 
 * @param t 
 * @return true 
 * @return false 
 */
bool Push(queue *q, const char* t);

/**
 * @brief 
 * 
 * @param q 
 * @return true 
 * @return false 
 */
bool Pop(queue *q);

/**
 * @brief 
 * 
 * @param q 
 * @return int 
 */
char* Top(const queue *q);

/**
 * @brief 
 * 
 * @param q 
 */
void Destroy(queue *q);

/**
 * @brief 
 * 
 * @param q 
 */
void Reverse(queue *q);