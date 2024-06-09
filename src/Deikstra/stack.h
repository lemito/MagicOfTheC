#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

/*Определяем стек вида Stack_Suffix с типом хранимых данных DataType*/
#define DEF_STACK(Suffix, DataType)                                            \
  typedef struct Stack_##Suffix##_Item_ {                                      \
    DataType data;                                                             \
    struct Stack_##Suffix##_Item_ *next;                                       \
  } Stack_##Suffix##_Item;                                                     \
                                                                               \
  typedef struct {                                                             \
    Stack_##Suffix##_Item *head;                                               \
    size_t size;                                                               \
  } Stack_##Suffix;                                                            \
                                                                               \
  Stack_##Suffix *Stack_##Suffix##_create() {                                  \
    Stack_##Suffix *stack = (Stack_##Suffix *)malloc(sizeof(Stack_##Suffix));  \
    stack->head =                                                              \
        (Stack_##Suffix##_Item *)malloc(sizeof(Stack_##Suffix##_Item));        \
    stack->size = 0;                                                           \
    return stack;                                                              \
  }                                                                            \
                                                                               \
  bool Stack_##Suffix##_empty(Stack_##Suffix *stack) {                         \
    return stack->size == 0;                                                   \
  }                                                                            \
                                                                               \
  size_t Stack_##Suffix##_size(Stack_##Suffix *stack) { return stack->size; }  \
                                                                               \
  bool Stack_##Suffix##_push(Stack_##Suffix *stack, DataType value) {    \
    Stack_##Suffix##_Item *new_head;                                           \
    if (!(new_head = (Stack_##Suffix##_Item *)malloc(                          \
              sizeof(Stack_##Suffix##_Item)))) {                               \
      return false;                                                            \
    }                                                                          \
                                                                               \
    new_head->next = stack->head;                                              \
    new_head->data = value;                                                    \
    stack->head = new_head;                                                    \
    stack->size++;                                                             \
    return true;                                                               \
  }                                                                            \
                                                                               \
  bool Stack_##Suffix##_pop(Stack_##Suffix *stack) {                           \
    if (Stack_##Suffix##_empty(stack)) {                                       \
      return false;                                                            \
    }                                                                          \
                                                                               \
    Stack_##Suffix##_Item *temp = stack->head;                                 \
    stack->head = stack->head->next;                                           \
    stack->size--;                                                             \
    free(temp);                                                                \
                                                                               \
    return true;                                                               \
  }                                                                            \
                                                                               \
  DataType *Stack_##Suffix##_top(Stack_##Suffix *stack) {                      \
    if (!Stack_##Suffix##_empty(stack)) {                                      \
      return &stack->head->data;                                               \
    }                                                                          \
    return NULL;                                                               \
  }                                                                            \
                                                                               \
  void Stack_##Suffix##_destroy(Stack_##Suffix *stack) {                       \
    while (!Stack_##Suffix##_empty(stack)) {                                   \
      Stack_##Suffix##_pop(stack);                                             \
    }                                                                          \
                                                                               \
    free(stack->head);                                                         \
    stack->head = NULL;                                                        \
    stack->size = 0;                                                           \
  }

#endif
