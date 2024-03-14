#include <stdlib.h>
#include <stdbool.h>
#ifndef STACK_ARR_LIB_H
#define STACK_ARR_LIB_H

#define POOL_SIZE 100

typedef struct
{
    int size;
    int data[POOL_SIZE];
} stack;

/**
 * @brief 
 * 
 * @param s 
 */
void Create(stack *s);
/**
 * @brief 
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool Empty(stack *s);
/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int Size(stack *s);
/**
 * @brief 
 * 
 * @param s 
 * @param t 
 * @return true 
 * @return false 
 */
bool Push(stack *s, int t);
/**
 * @brief 
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool Pop(stack *s);
/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int Top(stack *s);
/**
 * @brief 
 * 
 * @param s 
 */
void Destroy(stack *s);

#endif // STACK_ARR_LIB_H
