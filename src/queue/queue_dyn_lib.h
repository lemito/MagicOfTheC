#include <stdbool.h>

/**
 * @brief 
 * 
 */
struct Item
{
    int data;
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
bool Push(queue *q, const int t);

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
int Top(const queue *q);

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