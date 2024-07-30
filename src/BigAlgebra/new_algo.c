add = sum / 10;#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct block {
    struct block* next;
    struct block* prev;
    int data;
} block;

typedef struct BigInt {
    size_t size;
    block* blocks;
} BigInt;

typedef enum {
    NEGATIVE = -1,
    POSITIVE = 1,
} sign_t;

typedef struct BigFloat {
    sign_t sign;
    size_t exp;
    BigInt integer;
    BigInt fractal;
} BigFloat;

#define BLOCK_SIZE 8
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define BIGFLOAT_INIT(name) BigFloat name = {POSITIVE, 0, {0, NULL}, {0, NULL}}
#define BIGINT_INIT(name) BigInt name = {0, NULL}
// переопределение функций
/**
 * Выводит большой инт в консоль
 */
#define print_int(name) __print_int(&name)
#define init_float_from_str(dest, src ) __init_float_from_str(&dest, src);
/**
 * Создаёт большой инт из строки
 */
#define init_from_str(dest, src ) __init_from_str(&dest, src);
/**
 * Сложение: res = a+b
 * @param res BigInt с результатом
 * @param a
 * @param b
 */
#define BigInt_add(res, a, b) __BigInt_sum(&res, &a, &b)
/**
 * Очистить (удалить) BigInt
 */
#define BigInt_clear(dest) __Destroy_BigInt(&dest)

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

void __print_int(BigInt* myInt) {
    block* current = myInt->blocks;
    while(current != NULL) {
        printf("%d", current->data);
        current = current->next;
    }
//    printf("\n");
}

void __print_float(BigFloat * myFloat) {

    if (myFloat->sign == NEGATIVE) printf("-");
    print_int(myFloat->integer);
    printf(".");
    if (myFloat->exp > 0) print_int(myFloat->fractal);
    printf("\n");
}

[[maybe_unused]] void print_blocks(BigInt* myInt) {
    block* current = myInt->blocks;
    int cnt = 1;
    while(current != NULL) {
        printf("%d)%d\n", cnt, current->data);
        current = current->next;
        ++cnt;
    }
    printf("\n");
}

void __init_from_str(BigInt* dest, const char* src) {
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

void __init_float_from_str(BigFloat *dest, char* src){
    if (src[0] == '-') {
        dest->sign = NEGATIVE;
        src++;
    } else {
        dest->sign = POSITIVE;
    }
    char* sep = (char *)(".");
    char* istr = strtok(src, sep);
    printf("%s", istr);
//    char* posDot = (char*)(strchr(src, '.'));
//    if (posDot != NULL){
//        dest->exp = strlen(posDot) - 1;
//        *posDot = '\t';
//    }
//
//    init_from_str(dest->integer, src);
//
//    if (posDot!= NULL) {
//        init_from_str(dest->fractal, posDot + 1);
//    }
}

[[maybe_unused]] int poww(double base, double exp) {
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

void __BigInt_sum(BigInt *res, BigInt *a, BigInt *b) {
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

void __Destroy_BigInt(BigInt *bigInt) {
    block* current = bigInt->blocks;
    while (current != NULL) {
        block* nextBlock = current->next;
        free(current);
        current = nextBlock;
    }
    bigInt->blocks = NULL;
    bigInt->size = 0;
}


int main(){
    BIGINT_INIT(a);
    BIGINT_INIT(b);
    BIGINT_INIT(res);

    BIGFLOAT_INIT(my_float);


    init_from_str(a, "7412589632145698741258963214753698417525");

    init_from_str(b, "1234567890512345678912345671234561234563");

    init_float_from_str(my_float, "74125963.12321");

    print_int(a);
    printf("\n");

    printf("+\n");
    print_int(b);
    printf("\n");
//    my_float = {NEGATIVE, 1, a, b};
    BigInt_add(res, a, b);
    printf("=============================\n");
    print_int(res);
    printf("\n");

    printf("-----------------------------\n");

    __print_float(&my_float);

    BigInt_clear(a);
    BigInt_clear(b);
    BigInt_clear(res);
}