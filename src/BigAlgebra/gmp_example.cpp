#include <gmpxx.h>
#include <cstdio>

int main() {
    puts("Начало gmp");
    mpz_t x, y, result;

    mpz_init_set_str(x, "24691357819753086420", 10);
    mpz_init_set_str(y, "24691357819753086420", 10);
    mpz_init(result);

    mpz_add(result, x, y);
    gmp_printf("\t%Zd\n"
               "+\n"
               "\t%Zd\n"
               "--------------------\n"
               "\t%Zd\n", x, y, result);

    mpz_sub(result, x, y);
    gmp_printf("\t%Zd\n"
               "-\n"
               "\t%Zd\n"
               "--------------------\n"
               "\t%Zd\n", x, y, result);

    /* free used memory */
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(result);
    puts("Конец gmp");
    return 0;
}