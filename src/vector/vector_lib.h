#ifndef VECTOR_LAB_H
#define VECTOR_LAB_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Vector
{
    int *data;
    int size;
} Vector;

/**
 * @brief Creates an empty vector
 * 
 * @param v Pointer to an object of Vector structure
 * @param sz Initial size of the vector
 */
void Create(Vector *v, int sz);
/**
 * @brief Checks if the vector is empty
 * 
 * @param v Pointer to an object of Vector structure
 * @return true - Empty
 * @return false - Not empty
 */
bool Empty(Vector *v);
/**
 * @brief Get vector size
 * 
 * @param v Pointer to an object of Vector structure
 * @return int 
 */
int Size(Vector *v);
/**
 * @brief Get object by id as data[i], but vector
 * 
 * @param v Pointer to an object of Vector structure
 * @param i 
 * @return int 
 */
int Load(Vector *v, int i);
/**
 * @brief Add object t to vector by index as data[i] = t
 * 
 * @param v Pointer to an object of Vector structure
 * @param i index
 * @param t object
 */
void Save(Vector *v, int i, int t);
/**
 * @brief Resize
 * 
 * @param v Pointer to an object of Vector structure
 * @param sz 
 */
void Resize(Vector *v, int sz);
/**
 * @brief Checking for equivalence of vectors
 * 
 * @param l Pointer to an first object of Vector structure
 * @param r Pointer to an second object of Vector structure
 * @return true 
 * @return false 
 */
bool Eq(Vector *l, Vector *r);
/**
 * @brief Destroys the vector
 * 
 * @param v Pointer to an object of Vector structure
 */
void Destroy(Vector *v);

#endif // VECTOR_LAB_H

