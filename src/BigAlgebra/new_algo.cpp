#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <limits.h>

typedef struct block {
    struct block* next;
    struct block* prev;
    int data;
} block;

typedef struct BigInt {
    size_t size;
    block* blocks;
} BigInt;

#define BLOCK_SIZE 8
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#ifndef BIGINT_INIT
#define BIGINT_INIT(name) BigInt name = {0, NULL}
// переопределение функций
#define print_num(name) print_num_f(&name)
#define init_from_str(dest, src ) init_from_str_f(&dest, src);
/**
 * Сложение: res = a+b
 * @param res BigInt с результатом
 * @param a
 * @param b
 */
#define BigInt_add(res, a, b) BigInt_sum(&res, &a, &b)
#endif

block* create_block(int data) {
    block* newBlock = (block*)malloc(sizeof(block));
    if(newBlock == NULL) {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    newBlock->data = data;
    newBlock->prev = NULL;
    newBlock->next = NULL;
    return newBlock;
}

void add_block_to_bigint(BigInt* bigInt, block* newBlock) {
    if(bigInt->blocks == NULL) {
        bigInt->blocks = newBlock;
    } else {
        block* last = bigInt->blocks;
        while(last->next!= NULL) {
            last = last->next;
        }
        last->next = newBlock;
        newBlock->prev = last;
    }
    bigInt->size++;
}

void print_num_f(BigInt* myInt) {
    block* current = myInt->blocks;
    while(current != NULL) {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

void print_blocks(BigInt* myInt) {
    block* current = myInt->blocks;
    int cnt = 1;
    while(current != NULL) {
        printf("%d)%d\n", cnt, current->data);
        current = current->next;
        ++cnt;
    }
    printf("\n");
}


void init_from_str_f(BigInt* dest, const char* src) {
    size_t len = strlen(src);
    size_t numBlocks = len / BLOCK_SIZE;
    if (len % BLOCK_SIZE != 0) {
        numBlocks++;
    }

    size_t start = len % BLOCK_SIZE;
    if(start == 0) {
        start = BLOCK_SIZE;
    }

    block* currentBlock = create_block(0);
    dest->blocks = currentBlock;

    for (size_t i = 0; i < len; i++) {
        int digit = src[i] - '0';
        currentBlock->data = currentBlock->data * 10 + digit;
        start--;
        if (start == 0) {
            start = BLOCK_SIZE;
            if (i != len - 1) {
                block* newBlock = create_block(0);
                currentBlock->next = newBlock;
                newBlock->prev = currentBlock;
                currentBlock = newBlock;
            }
        }
    }

    dest->size = numBlocks;
}

int poww(double base, double exp) {
    long double answ = 1;
    if (exp < 0) {
        exp *= -1;
        for (int i = 0; i < exp; i++) answ *= base;
        answ = 1 / answ;
    } else if (exp > 0) {
        for (int i = 0; i < exp; i++) answ *= base;
    }
    return answ;
}

#define GO_TO_LAST(blockName) while (blockName != NULL && blockName->next != NULL) blockName = blockName->next;
#define GO_TO_PREV(blockName) if (blockName != NULL) blockName = blockName->prev;


void BigInt_sum(BigInt *res, BigInt *a, BigInt *b) {
    size_t lenn = MAX(a->size, b->size) + 1;
    res->size = lenn;
    res->blocks = NULL;

    block *curA = a->blocks;
    block *curB = b->blocks;
    GO_TO_LAST(curA);
    GO_TO_LAST(curB);

    int results[lenn];
    int add = 0;

    for (int i = lenn - 1; i >= 0; --i) {
        int valA = (curA != NULL) ? curA->data : 0;
        int valB = (curB != NULL) ? curB->data : 0;

        int sum = valA + valB + add;
        add = sum / 100000000;
        sum %= 100000000;

        results[i] = sum;

        GO_TO_PREV(curA);
        GO_TO_PREV(curB);
    }

    block *curRes = NULL;
    for (size_t i = 0; i < lenn; ++i) {
        block *newBlock = create_block(results[i]);
        if (curRes == NULL) {
            res->blocks = newBlock;
            curRes = newBlock;
        } else {
            curRes->next = newBlock;
            newBlock->prev = curRes;
            curRes = newBlock;
        }
    }
}


int main(){
    BIGINT_INIT(a);
    BIGINT_INIT(b);
    BIGINT_INIT(res);

    init_from_str(a, "12345678909876543210");

    init_from_str(b, "12345678909876543210");

    print_num(a);
    printf("+\n");
    print_num(b);

    BigInt_add(res, a, b);
    printf("=============================\n");
    print_num(res);
}