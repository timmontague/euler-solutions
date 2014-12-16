#include <stdio.h>
#include <gmp.h>

/*
 * The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
 *
 * Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
 */
int main(void) {
    int i;
    char *s = NULL;
    mpz_t n, temp;
    mpz_init(n);
    mpz_init(temp);
    for (i = 1; i <= 1000; i++) {
	mpz_ui_pow_ui(temp, i, i);
	mpz_add(n, n, temp);
    }
    i = gmp_asprintf(&s, "%Zd", n);
    printf("%s\n", s+i-10);
    return 0;
}
